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

        constexpr int kernelIdStart = 4;
        constexpr int sizeStart = 8;
        constexpr int ptrStart = 16;

        // KernelId (uint32_t)
        std::copy_n(buffer.begin() + kernelIdStart, sizeof(kernelId), reinterpret_cast<uint8_t *>(&kernelId));

        // Size (uint64_t)
        std::copy_n(buffer.begin() + sizeStart, sizeof(size), reinterpret_cast<uint8_t *>(&size));

        // Pointer (uint64_t)
        std::copy_n(buffer.begin() + ptrStart, sizeof(ptr), reinterpret_cast<uint8_t *>(&ptr));
    }
}
