/**
 * @file src/Gpu/Ipc/Message/serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"

namespace Gpu::Ipc {
    /**
     * @name serialize
     * @class Message
     * @namespace Gpu::Ipc
     * @brief This method serializes a Message object to return binary stream.
     * @return Common::Buffer8
     */
    Common::Buffer8 Message::serialize() const {
        // Create a 24-byte buffer.
        Common::Buffer8 buffer(24, 0);

        // CommandType as uint32_t (little endian)
        const auto type_int32 = static_cast<uint32_t>(type_);
        buffer[0] = static_cast<uint8_t>(type_int32 & 0xFF);
        buffer[1] = static_cast<uint8_t>((type_int32 >> 8) & 0xFF);
        buffer[2] = static_cast<uint8_t>((type_int32 >> 16) & 0xFF);
        buffer[3] = static_cast<uint8_t>((type_int32 >> 24) & 0xFF);

        // KernelId as uint32_t (little endian)
        buffer[4] = static_cast<uint8_t>(kernelId_ & 0xFF);
        buffer[5] = static_cast<uint8_t>((kernelId_ >> 8) & 0xFF);
        buffer[6] = static_cast<uint8_t>((kernelId_ >> 16) & 0xFF);
        buffer[7] = static_cast<uint8_t>((kernelId_ >> 24) & 0xFF);

        // Size in native little endian via memcpy
        memcpy(buffer.data() + 8,  &payload_size_, sizeof(payload_size_));

        // Ptr in native little endian via memcpy
        memcpy(buffer.data() + 16, &ptr_,  sizeof(ptr_));

        return buffer;
    }

} // namespace Gpu::Ipc
