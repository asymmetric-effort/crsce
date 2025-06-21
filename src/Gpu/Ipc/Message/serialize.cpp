/**
 * @file src/Gpu/Ipc/Message/serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Message.h"
#include <cstring>
#include <__utility/to_underlying.h>

namespace Gpu::Ipc {

    Common::Buffer8 Message::serialize() const {
        Common::Buffer8 buffer(24, 0);

        // CommandType as uint32_t (little endian)
        const uint32_t type_int = std::__to_underlying(type);
        buffer[0] = static_cast<uint8_t>(type_int & 0xFF);
        buffer[1] = static_cast<uint8_t>((type_int >> 8) & 0xFF);
        buffer[2] = static_cast<uint8_t>((type_int >> 16) & 0xFF);
        buffer[3] = static_cast<uint8_t>((type_int >> 24) & 0xFF);

        std::memcpy(buffer.data() + 4,  &kernelId, sizeof(kernelId));
        std::memcpy(buffer.data() + 8,  &size,     sizeof(size));
        std::memcpy(buffer.data() + 16, &ptr,      sizeof(ptr));

        return buffer;
    }

}
