#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

struct Room {
    std::string id;
    std::unordered_map<std::string, std::string> participants; // sessionId -> name
    std::chrono::system_clock::time_point createdAt;

    explicit Room(const std::string& rid)
        : id(rid), createdAt(std::chrono::system_clock::now()) {}
};

class RoomManager {
private:
    std::unordered_map<std::string, Room> rooms_;
    mutable std::mutex mutex_;
    std::mt19937_64 rng_;
    std::thread cleanupThread_;
    bool stop_{false};

    std::string generateRoomIdLocked() {
        std::uniform_int_distribution<int> dist(100000000, 999999999);
        int number = dist(rng_);
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(3) << (number / 1000000)
            << "-" << std::setw(3) << ((number / 1000) % 1000)
            << "-" << std::setw(3) << (number % 1000);
        return oss.str();
    }

    void cleanupLoop() {
        while (!stop_) {
            std::this_thread::sleep_for(std::chrono::minutes(5));
            std::lock_guard<std::mutex> lock(mutex_);
            auto now = std::chrono::system_clock::now();
            for (auto it = rooms_.begin(); it != rooms_.end();) {
                auto hours = std::chrono::duration_cast<std::chrono::hours>(
                    now - it->second.createdAt).count();
                if (hours >= 24 && it->second.participants.empty()) {
                    it = rooms_.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

public:
    RoomManager() {
        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        rng_.seed(seed);
        cleanupThread_ = std::thread(&RoomManager::cleanupLoop, this);
    }

    ~RoomManager() {
        stop_ = true;
        if (cleanupThread_.joinable()) cleanupThread_.join();
    }

    RoomManager(const RoomManager&) = delete;
    RoomManager& operator=(const RoomManager&) = delete;

    // Создаёт комнату с заданным ID, если её ещё нет (для webhook от LiveKit)
    void ensureRoom(const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (rooms_.count(roomId) == 0) {
            rooms_.emplace(roomId, Room(roomId));
        }
    }

    std::string createRoom() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::string roomId;
        do { roomId = generateRoomIdLocked(); } while (rooms_.count(roomId));
        rooms_.emplace(roomId, Room(roomId));
        return roomId;
    }

    bool roomExists(const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        return rooms_.count(roomId) > 0;
    }

    bool addParticipant(const std::string& roomId,
                        const std::string& sessionId,
                        const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = rooms_.find(roomId);
        if (it == rooms_.end()) return false;
        it->second.participants[sessionId] = name;
        return true;
    }

    void removeParticipant(const std::string& roomId,
                           const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = rooms_.find(roomId);
        if (it == rooms_.end()) return;
        it->second.participants.erase(sessionId);
        if (it->second.participants.empty()) rooms_.erase(it);
    }

    bool isInRoom(const std::string& sessionId, const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = rooms_.find(roomId);
        if (it == rooms_.end()) return false;
        return it->second.participants.count(sessionId) > 0;
    }

    std::vector<std::string> getParticipantIds(const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<std::string> out;
        auto it = rooms_.find(roomId);
        if (it == rooms_.end()) return out;
        out.reserve(it->second.participants.size());
        for (const auto& kv : it->second.participants) out.push_back(kv.first);
        return out;
    }

    size_t getParticipantCount(const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = rooms_.find(roomId);
        return (it == rooms_.end()) ? 0 : it->second.participants.size();
    }

    size_t getRoomCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return rooms_.size();
    }

    size_t getTotalParticipantCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        size_t total = 0;
        for (const auto& kv : rooms_) total += kv.second.participants.size();
        return total;
    }

    std::vector<std::pair<std::string, std::string>>
    getAllParticipants(const std::string& roomId) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<std::pair<std::string, std::string>> out;
        auto it = rooms_.find(roomId);
        if (it == rooms_.end()) return out;
        out.reserve(it->second.participants.size());
        for (const auto& kv : it->second.participants) out.push_back({kv.first, kv.second});
        return out;
    }
};

#endif // ROOM_MANAGER_H
