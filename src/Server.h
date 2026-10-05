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

    std::unordered_map<std::string, httplib::ws::WebSocket*> sessions_;
    std::shared_mutex sessionsMutex_;

    std::mutex logMutex_;

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

    static bool isValidName(const std::string& s) {
        if (s.empty() || s.size() > MAX_NAME_LENGTH) return false;
        for (unsigned char c : s) {
            if (c < 0x20 && c != '\t') return false;
            if (c == 0x7f) return false;
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

    void logEvent(const std::string& event) {
        std::lock_guard<std::mutex> lock(logMutex_);
        std::ofstream logFile("vidma_events.log", std::ios::app);
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            char timeStr[24];
            std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            logFile << "[" << timeStr << "] " << event << "\n";
        }
    }

    bool originAllowed(const httplib::Request& req) const {
        auto it = req.headers.find("Origin");
        if (it == req.headers.end()) return true; // non-browser or same-origin
        const std::string& o = it->second;
        if (o.find("vidma.online") != std::string::npos) return true;
        if (o.find("localhost") != std::string::npos) return true;
        if (o.find("127.0.0.1") != std::string::npos) return true;
        return false;
    }

    void setupHttpRoutes() {
        httpServer_.Get("/", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(VIDMA_HTML, "text/html; charset=utf-8");
        });

        httpServer_.Get("/robots.txt", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(
                "User-agent: *\nAllow: /\nSitemap: https://vidma.online/sitemap.xml\n",
                "text/plain");
        });

        httpServer_.Get("/sitemap.xml", [](const httplib::Request&, httplib::Response& res) {
            std::string sitemap =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n"
                "  <url><loc>https://vidma.online/</loc><changefreq>weekly</changefreq><priority>1.0</priority></url>\n"
                "</urlset>";
            res.set_content(sitemap, "application/xml; charset=utf-8");
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
            res.set_content(VIDMA_JS, "application/javascript; charset=utf-8");
        });

        httpServer_.Get("/api/health", [this](const httplib::Request&, httplib::Response& res) {
            json j;
            j["status"] = "ok";
            j["time"]   = (int64_t)std::time(nullptr);
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Get("/api/turn-credentials", [this](const httplib::Request&, httplib::Response& res) {
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
            try {
                json b = json::parse(req.body);
                json entry;
                entry["ts"]         = (int64_t)std::time(nullptr);
                entry["roomId"]     = b.value("roomId", std::string("unknown"));
                entry["rating"]     = b.value("rating", 0);
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
            logEvent("room_create id=" + roomId);

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
                        if (!n.empty() && isValidName(n)) name = n;
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
                    if (!n.empty() && isValidName(n)) name = n;
                }
            } catch (...) {}

            std::string identity = generateSecureSessionId();
            std::string token = makeLiveKitJwt(livekitApiKey_, livekitApiSecret_,
                                               roomId, identity, name, 3600);

            json j;
            j["roomId"]       = roomId;
            j["livekitUrl"]   = livekitUrl_;
            j["livekitToken"] = token;
            j["identity"]     = identity;
            res.set_header("Cache-Control", "no-store");
            res.set_content(j.dump(), "application/json");
        });

        httpServer_.Get(R"(/api/room/([^/]+)/exists)", [this](const httplib::Request& req, httplib::Response& res) {
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

    void setupWebSocketRoutes() {
        httpServer_.WebSocket("/ws", [this](const httplib::Request& req, httplib::ws::WebSocket& ws) {
            if (!originAllowed(req)) {
                ws.close(httplib::ws::CloseStatus::PolicyViolation);
                return;
            }

            std::string sessionId;
            std::string roomId;
            std::string name;
            bool joined = false;

            std::string msg;
            httplib::ws::ReadResult ret;
            while ((ret = ws.read(msg)) != httplib::ws::Fail) {
                if (ret != httplib::ws::Text) continue;
                if (msg.size() > MAX_MESSAGE_SIZE) {
                    ws.close(httplib::ws::CloseStatus::MessageTooBig);
                    break;
                }
                try {
                    json j = json::parse(msg);
                    std::string type = j.value("type", std::string{});

                    if (type == "join" && !joined) {
                        roomId = j.value("roomId", std::string{});
                        name   = j.value("name",   std::string{});

                        if (!isValidRoomId(roomId) || !isValidName(name)) {
                            json e; e["type"] = "error"; e["message"] = "invalid_input";
                            ws.send(e.dump());
                            ws.close(httplib::ws::CloseStatus::PolicyViolation);
                            return;
                        }
                        if (!roomManager_.roomExists(roomId)) {
                            json e; e["type"] = "error"; e["message"] = "room_not_found";
                            ws.send(e.dump());
                            ws.close(httplib::ws::CloseStatus::Normal);
                            return;
                        }
                        if (roomManager_.getParticipantCount(roomId) >= MAX_PARTICIPANTS_PER_ROOM) {
                            json e; e["type"] = "error"; e["message"] = "room_full";
                            ws.send(e.dump());
                            ws.close(httplib::ws::CloseStatus::PolicyViolation);
                            return;
                        }

                        sessionId = generateSecureSessionId();
                        auto existing = roomManager_.getAllParticipants(roomId);
                        roomManager_.addParticipant(roomId, sessionId, name);
                        joined = true;
                        {
                            std::unique_lock lock(sessionsMutex_);
                            sessions_[sessionId] = &ws;
                        }

                        logEvent("join room=" + roomId + " sid=" + sessionId +
                                 " ip=" + clientIpHash(req) +
                                 " name_len=" + std::to_string(name.size()));

                        json joinedMsg;
                        joinedMsg["type"]             = "joined";
                        joinedMsg["roomId"]           = roomId;
                        joinedMsg["sessionId"]        = sessionId; // server-issued
                        joinedMsg["participantCount"] = roomManager_.getParticipantCount(roomId);
                        ws.send(joinedMsg.dump());

                        for (const auto& [eid, ename] : existing) {
                            json m;
                            m["type"]      = "new-peer";
                            m["sessionId"] = eid;
                            m["name"]      = ename;
                            m["existing"]  = true;
                            ws.send(m.dump());
                        }

                        json newPeer;
                        newPeer["type"]      = "new-peer";
                        newPeer["sessionId"] = sessionId;
                        newPeer["name"]      = name;
                        broadcastToRoom(roomId, newPeer.dump(), sessionId);
                    }
                    else if (joined && (type == "offer" || type == "answer" || type == "ice-candidate")) {
                        std::string target = j.value("target", std::string{});
                        if (target.empty()) continue;
                        if (!roomManager_.isInRoom(target, roomId)) continue;
                        j["sender"] = sessionId;
                        forwardToSession(target, j.dump());
                    }
                } catch (...) {
                    // ignore malformed
                }
            }

            if (joined) {
                logEvent("leave room=" + roomId + " sid=" + sessionId);
                roomManager_.removeParticipant(roomId, sessionId);

                json left;
                left["type"]      = "peer-left";
                left["sessionId"] = sessionId;
                broadcastToRoom(roomId, left.dump(), sessionId);

                std::unique_lock lock(sessionsMutex_);
                sessions_.erase(sessionId);
            }
        });
    }

    void broadcastToRoom(const std::string& roomId, const std::string& message,
                         const std::string& excludeSessionId) {
        auto ids = roomManager_.getParticipantIds(roomId);
        std::shared_lock lock(sessionsMutex_);
        for (const auto& id : ids) {
            if (id == excludeSessionId) continue;
            auto it = sessions_.find(id);
            if (it != sessions_.end() && it->second && it->second->is_open()) {
                it->second->send(message);
            }
        }
    }

    void forwardToSession(const std::string& target, const std::string& message) {
        std::shared_lock lock(sessionsMutex_);
        auto it = sessions_.find(target);
        if (it != sessions_.end() && it->second && it->second->is_open()) {
            it->second->send(message);
        }
    }

public:
    explicit VideoCallServer(unsigned short port = 8080) : port_(port) {
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
        setupHttpRoutes();
        setupWebSocketRoutes();
    }

    void start() {
        std::cout << "Vidma server started on port " << port_ << "\n";
        httpServer_.listen("0.0.0.0", port_);
    }
};

#endif // SERVER_H
