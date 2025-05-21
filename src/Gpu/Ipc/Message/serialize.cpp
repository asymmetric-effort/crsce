// file: src/Gpu/Ipc/Message/serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Message.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cstring>

namespace Gpu::Ipc {

    std::vector<uint8_t> Message::serialize() const {
        std::vector<uint8_t> buffer(kFixedSize);
        std::memcpy(buffer.data(),        &type,     sizeof(type));
        std::memcpy(buffer.data() + 4,    &kernelId, sizeof(kernelId));
        std::memcpy(buffer.data() + 8,    &size,     sizeof(size));
        std::memcpy(buffer.data() + 16,   &ptr,      sizeof(ptr));
        return buffer;
    }

} // namespace Gpu::Ipc
