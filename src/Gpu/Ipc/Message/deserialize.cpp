// file: src/Gpu/Ipc/Message/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include "Gpu/Exceptions/InvalidIpcMessage.h"
#include <algorithm>
#include <cstdint>

namespace Gpu::Ipc {

    void Message::deserialize(const Common::Buffer8 &buffer) {
        if (buffer.size() != 24) {
            throw Exceptions::InvalidIpcMessage("deserialization expects 24-byte buffer");
        }

        // Extract CommandType (4 bytes little-endian)
        uint32_t type_int = 0;
        type_int |= static_cast<uint32_t>(buffer[0]);
        type_int |= static_cast<uint32_t>(buffer[1]) << 8;
        type_int |= static_cast<uint32_t>(buffer[2]) << 16;
        type_int |= static_cast<uint32_t>(buffer[3]) << 24;
        type_ = static_cast<CommandType>(type_int);

        // Extract kernelId (4 bytes little-endian)
        uint32_t kid_int = 0;
        kid_int |= static_cast<uint32_t>(buffer[4]);
        kid_int |= static_cast<uint32_t>(buffer[5]) << 8;
        kid_int |= static_cast<uint32_t>(buffer[6]) << 16;
        kid_int |= static_cast<uint32_t>(buffer[7]) << 24;
        kernelId_ = kid_int;

        // Extract size_ (8 bytes little-endian)
        uint64_t size_int = 0;
        for (int i = 0; i < 8; ++i) {
            size_int |= static_cast<uint64_t>(buffer[8 + i]) << (8 * i);
        }
        payload_size_ = static_cast<size_t>(size_int);

        // Extract ptr_ (8 bytes little-endian)
        uint64_t ptr_int = 0;
        for (int i = 0; i < 8; ++i) {
            ptr_int |= static_cast<uint64_t>(buffer[16 + i]) << (8 * i);
        }
        ptr_ = static_cast<Common::AbstractPtr>(ptr_int);
    }

} // namespace Gpu::Ipc
