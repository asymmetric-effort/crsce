/**
 * @file src/Gpu/Ipc/Message/deserialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"
#include <cstring>
#include <stdexcept>

#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/InvalidIpcMessage.h"

namespace Gpu::Ipc {

    void Message::deserialize(const Common::Buffer8& buffer) {
        if (buffer.size() != 24)
            throw Gpu::Exceptions::InvalidIpcMessage("deserialization expects 24-byte buffer");

        const uint8_t* data = buffer.data();

        type = static_cast<CommandType>(
            static_cast<uint32_t>(data[0]) |
            (static_cast<uint32_t>(data[1]) << 8) |
            (static_cast<uint32_t>(data[2]) << 16) |
            (static_cast<uint32_t>(data[3]) << 24)
        );

        std::memcpy(&kernelId, data + 4, sizeof(kernelId));
        std::memcpy(&size,     data + 8, sizeof(size));
        std::memcpy(&ptr,      data + 16, sizeof(ptr));
    }

}
