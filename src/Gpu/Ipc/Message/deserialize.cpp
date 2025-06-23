/**
 * @file src/Gpu/Ipc/Message/deserialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/InvalidIpcMessage.h"

namespace Gpu::Ipc
{
    /**
     * @name deserialize
     * @class Message
     * @namespace Gpu::Ipc
     * @brief This method deserializes a given binary string into the various properties of a message.
     * @param buffer
     */
    void Message::deserialize(const Common::Buffer8& buffer)
    {
        if (buffer.size() != 24)
            throw Exceptions::InvalidIpcMessage("deserialization expects 24-byte buffer");

        // CommandType is always 1 byte
        type_ = static_cast<CommandType>(buffer.at(0));

        constexpr auto kernelIdSz = sizeof(kernelId_);
        constexpr auto sizeSz = sizeof(size_);
        constexpr auto ptrSz = sizeof(ptr_);

        constexpr size_t kernelIdStart = 0;
        constexpr size_t sizeStart = kernelIdStart + kernelIdSz;
        constexpr size_t ptrStart = sizeStart + sizeSz;

        std::copy_n(buffer.begin() + kernelIdStart, kernelIdSz, reinterpret_cast<uint8_t*>(&kernelId_));
        std::copy_n(buffer.begin() + sizeStart, sizeSz, reinterpret_cast<uint8_t*>(&size_));
        std::copy_n(buffer.begin() + ptrStart, ptrSz, reinterpret_cast<uint8_t*>(&ptr_));
    }
}
