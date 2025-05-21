// file: src/Gpu/Ipc/Message/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include <cstddef>
#include <cstring>
#include <stdexcept>

namespace Gpu::Ipc {

    Message Message::deserialize(const uint8_t* data, size_t length) {
        if (length < kFixedSize || data == nullptr) {
            throw std::runtime_error("Message::deserialize: insufficient data");
        }

        Message msg;
        std::memcpy(&msg.type,     data,       sizeof(msg.type));
        std::memcpy(&msg.kernelId, data + 4,   sizeof(msg.kernelId));
        std::memcpy(&msg.size,     data + 8,   sizeof(msg.size));
        std::memcpy(&msg.ptr,      data + 16,  sizeof(msg.ptr));
        return msg;
    }

} // namespace Gpu::Ipc
