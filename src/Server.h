#ifndef SERVER_H
#define SERVER_H

#include "RoomManager.h"
#include <httplib.h>
#include <json.hpp>
#include "vidma_html.h"
#include "vidma_js.h"

#include <openssl/hmac.h>
#include <openssl/evp.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;

class VideoCallServer {
private:
    static constexpr size_t MAX_PARTICIPANTS_PER_ROOM = 10;
    static constexpr size_t MAX_NAME_LENGTH = 50;
    static constexpr size_t MAX_MESSAGE_SIZE = 64 * 1024;
    static constexpr int TURN_CRED_TTL_SECONDS = 5 * 60;

    httplib::Server httpServer_;
    RoomManager roomManager_;
    unsigned short port_;
    std::string turnSecret_;
    std::string livekitUrl_;
    std::string livekitApiKey_;
    std::string livekitApiSecret_;
    std::string turnHost_;
    int turnPort_;
    int turnTlsPort_;
    int64_t startTime_;

    mutable std::mutex logMutex_;

    // ---- base64 (no external deps beyond OpenSSL for HMAC) ----
    static std::string base64Encode(const unsigned char* data, size_t len) {
        static const char tbl[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string out;
        out.reserve(((len + 2) / 3) * 4);
        for (size_t i = 0; i < len; i += 3) {
            unsigned v = (unsigned)data[i] << 16;
            if (i + 1 < len) v |= (unsigned)data[i + 1] << 8;
            if (i + 2 < len) v |= (unsigned)data[i + 2];
            out.push_back(tbl[(v >> 18) & 63]);
            out.push_back(tbl[(v >> 12) & 63]);
            out.push_back(i + 1 < len ? tbl[(v >> 6) & 63] : '=');
            out.push_back(i + 2 < len ? tbl[v & 63] : '=');
        }
        return out;
    }

    static std::string hmacSha1Base64(const std::string& key, const std::string& data) {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digestLen = 0;
        HMAC(EVP_sha1(),
             key.data(), (int)key.size(),
             (const unsigned char*)data.data(), data.size(),
             digest, &digestLen);
        return base64Encode(digest, digestLen);
    }

    
    static std::string base64UrlEncode(const unsigned char* data, size_t len) {
        std::string b64 = base64Encode(data, len);
        while (!b64.empty() && b64.back() == '=') b64.pop_back();
        for (char& c : b64) {
            if (c == '+') c = '-';
            else if (c == '/') c = '_';
        }
        return b64;
    }

    static std::string base64UrlEncode(const std::string& s) {
        return base64UrlEncode((const unsigned char*)s.data(), s.size());
    }

    static std::string makeLiveKitJwt(
        const std::string& apiKey,
        const std::string& apiSecret,
        const std::string& roomId,
        const std::string& identity,
        const std::string& name,
        int ttlSeconds)
    {
        json header = {{"alg", "HS256"}, {"typ", "JWT"}};
        std::string h = base64UrlEncode(header.dump());

        int64_t now = (int64_t)std::time(nullptr);
        json payload = {
            {"iss", apiKey},
            {"sub", identity},
            {"nbf", now},
            {"exp", now + ttlSeconds},
            {"name", name},
            {"video", {
                {"room", roomId},
                {"roomJoin", true},
                {"canPublish", true},
                {"canSubscribe", true},
                {"canPublishData", true}
            }}
        };
        std::string p = base64UrlEncode(payload.dump());

        std::string signingInput = h + "." + p;

        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digestLen = 0;
        HMAC(EVP_sha256(),
             apiSecret.data(), (int)apiSecret.size(),
             (const unsigned char*)signingInput.data(), signingInput.size(),
             digest, &digestLen);

        return signingInput + "." + base64UrlEncode(digest, digestLen);
    }

    // ==================== WEBHOOK SIGNATURE VERIFICATION ====================

    static std::string base64UrlDecode(const std::string& in) {
        std::string s = in;
        for (char& c : s) { if (c == '-') c = '+'; else if (c == '_') c = '/'; }
        while (s.size() % 4) s.push_back('=');
        std::string out;
        out.resize((s.size() / 4) * 3);
        int n = EVP_DecodeBlock((unsigned char*)out.data(),
                                (const unsigned char*)s.data(),
                                (int)s.size());
        if (n < 0) return "";
        size_t pad = 0;
        if (!s.empty() && s[s.size() - 1] == '=') pad++;
        if (s.size() > 1 && s[s.size() - 2] == '=') pad++;
        out.resize((size_t)n - pad);
        return out;
    }

    static std::string sha256Base64(const std::string& data) {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int len = 0;
        EVP_Digest(data.data(), data.size(), digest, &len, EVP_sha256(), nullptr);
        return base64Encode(digest, len);
    }

    static bool constantTimeEq(const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        unsigned char diff = 0;
        for (size_t i = 0; i < a.size(); ++i) diff |= (unsigned char)(a[i] ^ b[i]);
        return diff == 0;
    }

    bool verifyLiveKitWebhook(const std::string& authHeader, const std::string& body) const {
        if (livekitApiSecret_.empty() || livekitApiKey_.empty()) return false;
        const std::string prefix = "Bearer ";
        if (authHeader.size() <= prefix.size()) return false;
        std::string token;
        if (authHeader.size() > prefix.size() && authHeader.compare(0, prefix.size(), prefix) == 0) {
            token = authHeader.substr(prefix.size());
        } else {
            token = authHeader;
        }
        while (!token.empty() && (token.back() == ' ' || token.back() == '\t')) token.pop_back();
        auto d1 = token.find('.');
        if (d1 == std::string::npos) return false;
        auto d2 = token.find('.', d1 + 1);
        if (d2 == std::string::npos) return false;
        std::string header_b64  = token.substr(0, d1);
        std::string payload_b64 = token.substr(d1 + 1, d2 - d1 - 1);
        std::string sig_b64     = token.substr(d2 + 1);

        std::string signingInput = header_b64 + "." + payload_b64;
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digestLen = 0;
        HMAC(EVP_sha256(),
             livekitApiSecret_.data(), (int)livekitApiSecret_.size(),
             (const unsigned char*)signingInput.data(), signingInput.size(),
             digest, &digestLen);
        std::string expected_sig_b64 = base64UrlEncode(digest, digestLen);
        if (!constantTimeEq(sig_b64, expected_sig_b64)) return false;

        std::string payloadJson = base64UrlDecode(payload_b64);
        if (payloadJson.empty()) return false;
        try {
            auto j = json::parse(payloadJson);
            std::string iss = j.value("iss", std::string());
            if (iss != livekitApiKey_) {
                logEvent(std::string("webhook_reject iss_mismatch in=") + iss + " expected=" + livekitApiKey_);
                return false;
            }
            std::string sha_in_token = j.value("sha256", std::string());
            if (!sha_in_token.empty()) {
                std::string body_hash = sha256Base64(body);
                if (!constantTimeEq(sha_in_token, body_hash)) return false;
            }
            int64_t exp = j.value("exp", (int64_t)0);
            if (exp > 0 && (int64_t)std::time(nullptr) > exp) return false;
        } catch (...) { return false; }
        return true;
    }

    static std::string generateSecureSessionId() {
        static thread_local std::mt19937_64 rng{std::random_device{}()};
        std::uniform_int_distribution<uint64_t> dist;
        char buf[40];
        std::snprintf(buf, sizeof(buf), "%016llx%016llx",
                      (unsigned long long)dist(rng),
                      (unsigned long long)dist(rng));
        return std::string(buf);
    }

    static bool isValidRoomId(const std::string& s) {
        if (s.size() != 11) return false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (i == 3 || i == 7) {
                if (s[i] != '-') return false;
            } else if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }

    // Убирает всё опасное из имени: HTML-теги, control chars, угловые скобки
    static std::string sanitizeName(const std::string& input) {
        if (input.empty()) return "";
        std::string out;
        out.reserve(input.size());

        // Проходим по UTF-8 байтам и выкидываем опасные
        for (size_t i = 0; i < input.size(); ) {
            unsigned char c = (unsigned char)input[i];

            // Управляющие символы (0x00–0x1F, 0x7F) — выкидываем
            if (c < 0x20 || c == 0x7F) { i++; continue; }

            // Угловые скобки, амперсанд, кавычки, обратный слэш — выкидываем
            if (c == '<' || c == '>' || c == '&' || c == '"' || c == '\'' || c == '\\') {
                i++; continue;
            }

            // Для UTF-8 многобайтных — пропускаем байты как есть, но ограничиваем
            if (c >= 0x80) {
                // Определяем длину UTF-8 последовательности
                int len = 1;
                if ((c & 0xE0) == 0xC0) len = 2;
                else if ((c & 0xF0) == 0xE0) len = 3;
                else if ((c & 0xF8) == 0xF0) len = 4;

                if (i + len > input.size()) { i++; continue; }
                // Пропускаем всю последовательность
                for (int k = 0; k < len; k++) out.push_back(input[i + k]);
                i += len;
                continue;
            }

            out.push_back((char)c);
            i++;
        }

        // Trim
        while (!out.empty() && (out.back() == ' ' || out.back() == '\t')) out.pop_back();
        while (!out.empty() && (out.front() == ' ' || out.front() == '\t')) out.erase(out.begin());

        // Ограничиваем длину
        if (out.size() > MAX_NAME_LENGTH) out = out.substr(0, MAX_NAME_LENGTH);

        // Если после очистки пусто — вернём пустую строку
        return out;
    }

    static bool isValidName(const std::string& s) {
        if (s.empty() || s.size() > MAX_NAME_LENGTH) return false;
        for (unsigned char c : s) {
            if (c < 0x20 && c != '\t') return false;
            if (c == 0x7F) return false;
        }
        return true;
    }

    static std::string clientIpHash(const httplib::Request& req) {
        std::string ip = req.remote_addr;
        auto it = req.headers.find("X-Forwarded-For");
        if (it != req.headers.end()) {
            std::string xff = it->second;
            auto comma = xff.find(',');
            if (comma != std::string::npos) xff = xff.substr(0, comma);
            while (!xff.empty() && (xff.back() == ' ' || xff.back() == '\t')) xff.pop_back();
            while (!xff.empty() && (xff.front() == ' ' || xff.front() == '\t')) xff.erase(xff.begin());
            if (!xff.empty()) ip = xff;
        }
        uint64_t h = 1469598103934665603ULL;
        for (unsigned char c : ip) { h ^= c; h *= 1099511628211ULL; }
        char buf[24];
        std::snprintf(buf, sizeof(buf), "%016llx", (unsigned long long)h);
        return std::string(buf);
    }

    void logEvent(const std::string& event) const {
        std::lock_guard<std::mutex> lock(logMutex_);
        std::ofstream logFile("vidma_events.log", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            char timeStr[24];
            std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            logFile << "[" << timeStr << "] " << event << "\n";
        }
    }

    static bool isAllowedOrigin(const std::string& o) {
        static const char* allowed[] = {
            "https://vidma.online",
            "https://www.vidma.online",
            "http://vidma.online",
            "http://localhost:8080",
            "http://localhost:3000",
            "http://127.0.0.1:8080",
            nullptr
        };
        for (int i = 0; allowed[i]; ++i) if (o == allowed[i]) return true;
        return false;
    }

    static std::string clientIp(const httplib::Request& req) {
        auto it = req.headers.find("X-Real-IP");
        if (it != req.headers.end() && !it->second.empty()) return it->second;
        auto xff = req.headers.find("X-Forwarded-For");
        if (xff != req.headers.end() && !xff->second.empty()) {
            auto c = xff->second.find(',');
            return c == std::string::npos ? xff->second : xff->second.substr(0, c);
        }
        return req.remote_addr;
    }

    bool originAllowed(const httplib::Request& req) const {
        auto it = req.headers.find("Origin");
        if (it == req.headers.end()) return true;
        return isAllowedOrigin(it->second);
    }

    // ---- Localized landing metadata ----
    struct LangMeta {
        const char* code;
        const char* title;
        const char* description;
        const char* h1;
    };

    static const LangMeta* findLangMeta(const std::string& lang) {
        static const LangMeta metas[] = {
            {"en", "Vidma — Free Video Calls Without Registration",
                   "Vidma is a free browser-based video calling service. Create a room in seconds, invite friends — no registration, no downloads, works on any device.",
                   "Video calls in one click"},
            {"ru", "Vidma — Бесплатные видеозвонки без регистрации",
                   "Vidma — бесплатные видеозвонки в браузере. Создайте комнату за секунды, пригласите друзей — без регистрации и установки, работает на любом устройстве.",
                   "Видеозвонки в один клик"},
            {"es", "Vidma — Videollamadas gratis sin registro",
                   "Vidma es un servicio gratuito de videollamadas en el navegador. Crea una sala en segundos, invita a amigos — sin registro ni descargas.",
                   "Videollamadas en un clic"},
            {"de", "Vidma — Kostenlose Videoanrufe ohne Registrierung",
                   "Vidma ist ein kostenloser Videoanrufdienst im Browser. Erstelle in Sekunden einen Raum, lade Freunde ein — ohne Registrierung.",
                   "Videoanrufe mit einem Klick"},
            {"fr", "Vidma — Appels vidéo gratuits sans inscription",
                   "Vidma est un service gratuit d'appels vidéo dans le navigateur. Créez une salle en quelques secondes, invitez vos amis — sans inscription.",
                   "Appels vidéo en un clic"},
            {"zh", "Vidma — 免费视频通话，无需注册",
                   "Vidma 是浏览器中的免费视频通话服务。几秒钟即可创建房间，邀请朋友 — 无需注册，无需下载。",
                   "一键视频通话"},
            {"ja", "Vidma — 登録不要の無料ビデオ通話",
                   "Vidma はブラウザで使える無料のビデオ通話サービスです。数秒でルームを作成し、友達を招待できます — 登録不要。",
                   "ワンクリックでビデオ通話"},
            {"pt", "Vidma — Chamadas de vídeo grátis sem registro",
                   "Vidma é um serviço gratuito de chamadas de vídeo no navegador. Crie uma sala em segundos, convide amigos — sem registro.",
                   "Chamadas de vídeo em um clique"},
            {"pl", "Vidma — Darmowe wideorozmowy bez rejestracji",
                   "Vidma to darmowy serwis wideorozmów w przeglądarce. Utwórz pokój w kilka sekund, zaproś znajomych — bez rejestracji i instalacji.",
                   "Wideorozmowy jednym kliknięciem"},
            {"uk", "Vidma — Безкоштовні відеодзвінки без реєстрації",
                   "Vidma — безкоштовний сервіс відеодзвонків у браузері. Створіть кімнату за секунди, запросіть друзів — без реєстрації та встановлення.",
                   "Відеодзвінки одним кліком"},
            {nullptr, nullptr, nullptr, nullptr}
        };
        for (int i = 0; metas[i].code; ++i) {
            if (lang == metas[i].code) return &metas[i];
        }
        return nullptr;
    }

    static std::string renderLanding(const std::string& lang) {
        std::string html(VIDMA_HTML);
        const LangMeta* m = findLangMeta(lang);
        if (!m) m = findLangMeta("en");
        if (!m) return html;
        auto ra = [](std::string& s, const std::string& from, const std::string& to) {
            if (from.empty()) return;
            size_t pos = 0;
            while ((pos = s.find(from, pos)) != std::string::npos) {
                s.replace(pos, from.size(), to);
                pos += to.size();
            }
        };
        std::string canonical = (lang == "en")
            ? std::string("https://vidma.online/")
            : std::string("https://vidma.online/") + lang + "/";
        ra(html, "{{LANG}}",        std::string(m->code));
        ra(html, "{{TITLE}}",       std::string(m->title));
        ra(html, "{{DESCRIPTION}}", std::string(m->description));
        ra(html, "{{H1}}",          std::string(m->h1));
        ra(html, "{{CANONICAL}}",   canonical);
        return html;
    }

    void setupHttpRoutes() {
        // Landing — English (default, x-default)
        httpServer_.Get("/", [this](const httplib::Request&, httplib::Response& res) {
            res.set_content(renderLanding("en"), "text/html; charset=utf-8");
            res.set_header("Cache-Control", "public, max-age=300");
        });

        // Localized landing: /ru/ /pl/ /uk/ /es/ /de/ /fr/ /zh/ /ja/ /pt/
        // /en → 301 / (no duplicate)
        httpServer_.Get(R"(/([a-z]{2})/?)", [this](const httplib::Request& req, httplib::Response& res) {
            std::string lang = req.matches[1].str();
            std::string path = req.path;
            if (lang == "en") {
                res.status = 301;
                res.set_header("Location", "/");
                return;
            }
            if (!findLangMeta(lang)) {
                res.status = 404;
                res.set_content("Not found", "text/plain; charset=utf-8");
                return;
            }
            if (path.empty() || path.back() != '/') {
                res.status = 301;
                res.set_header("Location", "/" + lang + "/");
                return;
            }
            res.set_content(renderLanding(lang), "text/html; charset=utf-8");
            res.set_header("Cache-Control", "public, max-age=300");
        });

        httpServer_.Get("/robots.txt", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(
                "User-agent: *\nAllow: /\nSitemap: https://vidma.online/sitemap.xml\n",
                "text/plain");
        });

        httpServer_.Get("/sitemap.xml", [](const httplib::Request&, httplib::Response& res) {
            std::string sitemap =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n";
            sitemap += "  <url><loc>https://vidma.online/</loc><lastmod>2026-10-09</lastmod><changefreq>weekly</changefreq><priority>1.0</priority></url>\n";
            static const char* langs[] = {"ru","es","de","fr","zh","ja","pt","pl","uk",nullptr};
            for (int i = 0; langs[i]; ++i) {
                sitemap += "  <url><loc>https://vidma.online/";
                sitemap += langs[i];
                sitemap += "/</loc><lastmod>2026-10-09</lastmod><changefreq>weekly</changefreq><priority>0.9</priority></url>\n";
            }
            sitemap += "  <url><loc>https://vidma.online/privacy</loc><changefreq>monthly</changefreq><priority>0.5</priority></url>\n";
            sitemap += "  <url><loc>https://vidma.online/terms</loc><changefreq>monthly</changefreq><priority>0.5</priority></url>\n";
            sitemap += "</urlset>";
            res.set_content(sitemap, "application/xml; charset=utf-8");
            res.set_header("Cache-Control", "public, max-age=3600");
        });

        httpServer_.Get("/privacy", [](const httplib::Request&, httplib::Response& res) {
            std::string html =
                "<!DOCTYPE html><html lang=\"ru\"><head><meta charset=\"UTF-8\">"
                "<title>Политика конфиденциальности — Vidma</title></head>"
                "<body style=\"font-family:sans-serif;max-width:800px;margin:2em auto;\">"
                "<h1>Политика конфиденциальности</h1>"
                "<p>Мы не храним историю звонков. Разговоры не записываются. "
                "Медиа-соединения устанавливаются напрямую между участниками "
                "(WebRTC, DTLS-SRTP).</p>"
                "<p><a href=\"/\">На главную</a></p></body></html>";
            res.set_content(html, "text/html; charset=utf-8");
        });

        httpServer_.Get("/terms", [](const httplib::Request&, httplib::Response& res) {
            std::string html =
                "<!DOCTYPE html><html lang=\"ru\"><head><meta charset=\"UTF-8\">"
                "<title>Условия использования — Vidma</title></head>"
                "<body style=\"font-family:sans-serif;max-width:800px;margin:2em auto;\">"
                "<h1>Условия использования</h1>"
                "<p>Сервис предоставляется «как есть». Запрещено использовать "
                "для незаконной деятельности.</p>"
                "<p><a href=\"/\">На главную</a></p></body></html>";
            res.set_content(html, "text/html; charset=utf-8");
        });

        httpServer_.Get("/favicon.ico", [](const httplib::Request&, httplib::Response& res) {
            std::ifstream f("favicon.ico", std::ios::binary);
            if (!f) { res.status = 404; return; }
            std::string content((std::istreambuf_iterator<char>(f)),
                                 std::istreambuf_iterator<char>());
            res.set_content(content, "image/x-icon");
        });

        httpServer_.Get("/app.js", [](const httplib::Request&, httplib::Response& res) {
            res.set_header("Cache-Control", "public, max-age=300");
            res.set_content(VIDMA_JS, "application/javascript; charset=utf-8");
        });

        httpServer_.Post("/api/livekit-webhook", [this](const httplib::Request& req, httplib::Response& res) {
            {
                auto authIt = req.headers.find("Authorization");
                if (authIt == req.headers.end()) {
                    logEvent("webhook_reject no_auth");
                    res.status = 401;
                    res.set_content(R"({"ok":false,"error":"no_auth"})", "application/json");
                    return;
                }
                if (!verifyLiveKitWebhook(authIt->second, req.body)) {
                    logEvent("webhook_reject bad_signature");
                    res.status = 401;
                    res.set_content(R"({"ok":false,"error":"bad_signature"})", "application/json");
                    return;
                }
            }
            try {
                auto j = json::parse(req.body);
                std::string event = j.value("event", std::string());

                // room_started / room_finished
                if (event == "room_started" || event == "room_finished") {
                    std::string room = j.value("room", json::object()).value("name", std::string("?"));
                    logEvent("lk_" + event + " room=" + room);
                }
                // participant_joined / participant_left
                else if (event == "participant_joined" || event == "participant_left") {
                    auto p = j.value("participant", json::object());
                    std::string identity = p.value("identity", std::string("?"));
                    std::string name = p.value("name", std::string("Гость"));
                    std::string room = j.value("room", json::object()).value("name", std::string("?"));

                    // sanitize
                    std::string safe = sanitizeName(name);
                    if (safe.empty()) safe = "Гость";

                    if (event == "participant_joined") {
                        roomManager_.ensureRoom(room);
                        roomManager_.addParticipant(room, identity, safe);
                        size_t cnt = roomManager_.getParticipantCount(room);
                        logEvent("join room=" + room + " sid=" + identity + " name=" + safe +
                                 " count=" + std::to_string(cnt));
                    } else {
                        size_t before = roomManager_.getParticipantCount(room);
                        size_t rem = before > 0 ? before - 1 : 0;
                        logEvent("leave room=" + room + " sid=" + identity + " name=" + safe +
                                 " remaining=" + std::to_string(rem));
                        roomManager_.removeParticipant(room, identity);
                        if (rem == 0) {
                            logEvent("room_closed id=" + room + " last_user=" + safe);
                        }
                    }
                }

                res.set_content(R"({"ok":true})", "application/json");
            } catch (const std::exception& e) {
                res.status = 400;
                res.set_content(R"({"ok":false})", "application/json");
            }
        });

        httpServer_.Get("/api/health", [this](const httplib::Request&, httplib::Response& res) {
            json j;
            j["status"] = "ok";
            j["time"]   = (int64_t)std::time(nullptr);
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Get("/api/stats", [this](const httplib::Request&, httplib::Response& res) {
            json j;
            j["status"]       = "ok";
            j["time"]         = (int64_t)std::time(nullptr);
            j["uptime"]       = (int64_t)(std::time(nullptr) - startTime_);
            j["rooms"]        = (int64_t)roomManager_.getRoomCount();
            j["participants"] = (int64_t)roomManager_.getTotalParticipantCount();
            res.set_header("Cache-Control", "no-store");
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Get("/api/turn-credentials", [this](const httplib::Request& req, httplib::Response& res) {
            auto oit = req.headers.find("Origin");
            if (oit != req.headers.end() && !isAllowedOrigin(oit->second)) {
                res.status = 403;
                res.set_content(R"({"error":"forbidden_origin"})", "application/json");
                return;
            }
            static std::mutex rlM;
            static std::unordered_map<std::string, std::pair<int64_t, int>> rlMap;
            std::string ip = clientIp(req);
            int64_t now = (int64_t)std::time(nullptr);
            {
                std::lock_guard<std::mutex> lk(rlM);
                auto& e = rlMap[ip];
                if (now - e.first > 60) { e.first = now; e.second = 0; }
                if (++e.second > 10) {
                    res.status = 429;
                    res.set_header("Retry-After", "60");
                    res.set_content(R"({"error":"rate_limited"})", "application/json");
                    return;
                }
            }
            if (turnSecret_.empty()) {
                res.status = 503;
                res.set_content(R"({"error":"turn_not_configured"})", "application/json");
                return;
            }
            int64_t expiry = (int64_t)std::time(nullptr) + TURN_CRED_TTL_SECONDS;
            std::string username = std::to_string(expiry) + ":vidma";
            std::string credential = hmacSha1Base64(turnSecret_, username);
            std::string host = turnHost_.empty() ? "vidma.online" : turnHost_;
            json j;
            j["urls"] = {
                "turn:" + host + ":" + std::to_string(turnPort_) + "?transport=udp",
                "turn:" + host + ":" + std::to_string(turnPort_) + "?transport=tcp"
            };
            j["username"]   = username;
            j["credential"] = credential;
            j["ttl"]        = TURN_CRED_TTL_SECONDS;
            res.set_header("Cache-Control", "no-store");
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Post("/api/feedback", [this](const httplib::Request& req, httplib::Response& res) {
            auto oit = req.headers.find("Origin");
            if (oit != req.headers.end() && !isAllowedOrigin(oit->second)) {
                res.status = 403;
                res.set_content(R"({"status":"error","message":"forbidden_origin"})", "application/json");
                return;
            }
            if (req.body.size() > 8192) {
                res.status = 413;
                res.set_content(R"({"status":"error","message":"body_too_large"})", "application/json");
                return;
            }
            static std::mutex fbM;
            static std::unordered_map<std::string, std::pair<int64_t, int>> fbMap;
            std::string fip = clientIp(req);
            int64_t fnow = (int64_t)std::time(nullptr);
            {
                std::lock_guard<std::mutex> lk(fbM);
                auto& e = fbMap[fip];
                if (fnow - e.first > 60) { e.first = fnow; e.second = 0; }
                if (++e.second > 5) {
                    res.status = 429;
                    res.set_header("Retry-After", "60");
                    res.set_content(R"({"status":"error","message":"rate_limited"})", "application/json");
                    return;
                }
            }
            try {
                json b = json::parse(req.body);
                json entry;
                entry["ts"]         = (int64_t)std::time(nullptr);
                entry["roomId"]     = b.value("roomId", std::string("unknown"));
                int rv = b.value("rating", 0);
                if (rv < 0 || rv > 5) rv = 0;
                entry["rating"]     = rv;
                entry["comment"]    = b.value("comment", std::string());
                entry["userAgent"]  = b.value("userAgent", std::string());
                entry["ipHash"]     = clientIpHash(req);
                // cap sizes
                if (entry["comment"].is_string() && entry["comment"].get<std::string>().size() > 1000) {
                    entry["comment"] = entry["comment"].get<std::string>().substr(0, 1000);
                }
                if (entry["userAgent"].is_string() && entry["userAgent"].get<std::string>().size() > 300) {
                    entry["userAgent"] = entry["userAgent"].get<std::string>().substr(0, 300);
                }
                std::ofstream fb("/var/log/vidma-feedback.jsonl", std::ios::app);
                if (fb.is_open()) fb << entry.dump() << "\n";
                json ok; ok["status"] = "ok";
                res.set_content(ok.dump(), "application/json");
            } catch (const std::exception& e) {
                json err; err["status"] = "error"; err["message"] = e.what();
                res.status = 400;
                res.set_content(err.dump(), "application/json");
            }
        });

        httpServer_.Post("/api/room/create", [this](const httplib::Request& req, httplib::Response& res) {
            std::string roomId = roomManager_.createRoom();
            std::string dbg = "room_create id=" + roomId + " body=" + req.body.substr(0, 200);
            logEvent(dbg);

            json j;
            j["roomId"]          = roomId;
            j["success"]         = true;
            j["maxParticipants"] = MAX_PARTICIPANTS_PER_ROOM;

            if (!livekitApiKey_.empty() && !livekitApiSecret_.empty()) {
                std::string name = "\xd0\x93\xd0\xbe\xd1\x81\xd1\x82\xd1\x8c"; // "Гость"
                try {
                    if (!req.body.empty()) {
                        json b = json::parse(req.body);
                        std::string n = b.value("name", std::string());
                        if (!n.empty()) {
                        std::string cleaned = sanitizeName(n);
                        if (!cleaned.empty() && isValidName(cleaned)) name = cleaned;
                    }
                    }
                } catch (...) {}
                std::string identity = generateSecureSessionId();
                std::string token = makeLiveKitJwt(livekitApiKey_, livekitApiSecret_,
                                                   roomId, identity, name, 3600);
                j["livekitUrl"]   = livekitUrl_;
                j["livekitToken"] = token;
                j["identity"]     = identity;
            }

            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Post(R"(/api/room/([0-9\-]+)/token)", [this](const httplib::Request& req, httplib::Response& res) {
            std::string roomId = req.matches[1];
            if (!isValidRoomId(roomId)) {
                res.status = 400;
                res.set_content(R"({"error":"invalid_room_id"})", "application/json");
                return;
            }
            if (!roomManager_.roomExists(roomId)) {
                res.status = 404;
                res.set_content(R"({"error":"room_not_found"})", "application/json");
                return;
            }
            if (livekitApiKey_.empty() || livekitApiSecret_.empty()) {
                res.status = 503;
                res.set_content(R"({"error":"livekit_not_configured"})", "application/json");
                return;
            }

            std::string name = "\xd0\x93\xd0\xbe\xd1\x81\xd1\x82\xd1\x8c";
            try {
                if (!req.body.empty()) {
                    json b = json::parse(req.body);
                    std::string n = b.value("name", std::string());
                    if (!n.empty()) {
                        std::string cleaned = sanitizeName(n);
                        if (!cleaned.empty() && isValidName(cleaned)) name = cleaned;
                    }
                }
            } catch (...) {}

            std::string identity = generateSecureSessionId();
            std::string token = makeLiveKitJwt(livekitApiKey_, livekitApiSecret_,
                                               roomId, identity, name, 3600);
            logEvent("token_req room=" + roomId + " name=" + name);

            json j;
            j["roomId"]       = roomId;
            j["livekitUrl"]   = livekitUrl_;
            j["livekitToken"] = token;
            j["identity"]     = identity;
            res.set_header("Cache-Control", "no-store");
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Get(R"(/api/room/([0-9\-]+)/exists)", [this](const httplib::Request& req, httplib::Response& res) {
            std::string roomId = req.matches[1];
            if (!isValidRoomId(roomId)) {
                res.status = 400;
                res.set_content(R"({"error":"invalid_room_id"})", "application/json");
                return;
            }
            json j;
            j["exists"] = roomManager_.roomExists(roomId);
            j["roomId"] = roomId;
            res.set_content(j.dump(), "application/json");
        });
    }

public:
    explicit VideoCallServer(unsigned short port = 8080) : port_(port), startTime_((int64_t)std::time(nullptr)) {
        const char* secret = std::getenv("TURN_SECRET");
        if (const char* v = std::getenv("LIVEKIT_URL"))         livekitUrl_ = v;
        if (const char* v = std::getenv("LIVEKIT_API_KEY"))     livekitApiKey_ = v;
        if (const char* v = std::getenv("LIVEKIT_API_SECRET"))  livekitApiSecret_ = v;
        turnSecret_ = secret ? secret : "";
        const char* thost = std::getenv("TURN_HOST");
        turnHost_ = thost ? thost : "";
        turnPort_ = 3478;
        turnTlsPort_ = 5349;
        if (const char* p = std::getenv("TURN_PORT"))     turnPort_    = std::atoi(p);
        if (const char* p = std::getenv("TURN_TLS_PORT")) turnTlsPort_ = std::atoi(p);
        if (turnSecret_.empty()) {
            std::cerr << "[WARN] TURN_SECRET not set — /api/turn-credentials will return 503\n";
        }
        httpServer_.set_payload_max_length(MAX_MESSAGE_SIZE);
        httpServer_.set_read_timeout(15, 0);
        httpServer_.set_write_timeout(15, 0);
        setupHttpRoutes();
    }

    void start() {
        std::cout << "Vidma server started on port " << port_ << "\n";
        httpServer_.listen("0.0.0.0", port_);
    }
};

#endif // SERVER_H
