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
    void Message::deserialize(const Common::Buffer8 &buffer) {
        if (buffer.size() != 24)
            throw Gpu::Exceptions::InvalidIpcMessage("deserialization expects 24-byte buffer");

        // CommandType is always 1 byte
        type = static_cast<CommandType>(buffer.at(0));

        constexpr size_t kernelIdStart = 0;
        constexpr size_t sizeStart     = kernelIdStart + sizeof(kernelId);
        constexpr size_t ptrStart      = sizeStart     + sizeof(size);

        std::copy_n(buffer.begin() + kernelIdStart, sizeof(kernelId), reinterpret_cast<uint8_t *>(&kernelId));
        std::copy_n(buffer.begin() + sizeStart,     sizeof(size),     reinterpret_cast<uint8_t *>(&size));
        std::copy_n(buffer.begin() + ptrStart,      sizeof(ptr),      reinterpret_cast<uint8_t *>(&ptr));
    }
}
