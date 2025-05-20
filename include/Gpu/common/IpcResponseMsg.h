// file: include/Gpu/common/IpcResponseMsg.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <type_traits>

class IpcResponseMsg {
public:
    uint8_t status = 1; // 0 = success, nonzero = error code
    uint64_t size = 0; // payload size in bytes
    std::vector<uint8_t> data;

    IpcResponseMsg() = default;

    IpcResponseMsg(const uint8_t s, const void *payload, const uint64_t payloadSize)
        : status(s), size(payloadSize),
          data(static_cast<const uint8_t *>(payload),
               static_cast<const uint8_t *>(payload) + payloadSize) {}

    // Serialize this message to a raw byte stream for IPC
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer;
        buffer.reserve(1 + sizeof(size) + data.size());
        buffer.push_back(status);
        uint64_t sizeLE = size;
        const uint8_t *pSize = reinterpret_cast<const uint8_t *>(&sizeLE);
        buffer.insert(buffer.end(), pSize, pSize + sizeof(uint64_t));
        buffer.insert(buffer.end(), data.begin(), data.end());
        return buffer;
    }

    // Deserialize a message from raw bytes
    static IpcResponseMsg deserialize(const uint8_t *buffer, size_t length) {
        if (length < 1 + sizeof(uint64_t)) {
            throw std::runtime_error("IpcResponseMsg: buffer too small to deserialize");
        }

        IpcResponseMsg msg;
        msg.status = buffer[0];

        std::memcpy(&msg.size, buffer + 1, sizeof(uint64_t));
        if (length < 1 + sizeof(uint64_t) + msg.size) {
            throw std::runtime_error("IpcResponseMsg: declared size exceeds buffer");
        }

        msg.data.assign(buffer + 1 + sizeof(uint64_t), buffer + 1 + sizeof(uint64_t) + msg.size);
        return msg;
    }

    template<typename T>
    T as() const {
        static_assert(std::is_trivially_copyable_v<T>, "IpcResponseMsg::as<T>() requires trivially copyable type");
        if (sizeof(T) > data.size()) {
            throw std::runtime_error("IpcResponseMsg::as<T>() payload too small");
        }
        T value;
        std::memcpy(&value, data.data(), sizeof(T));
        return value;
    }
};
