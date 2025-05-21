// file: src/Gpu/Ipc/Response/serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Response.h"
#include <cstring>

namespace Gpu::Ipc {

    std::vector<uint8_t> Response::serialize() const {
        std::vector<uint8_t> buffer(kFixedHeaderSize + data.size());

        buffer[0] = status;
        std::memcpy(buffer.data() + 1, &size, sizeof(size));

        if (!data.empty()) {
            std::memcpy(buffer.data() + kFixedHeaderSize, data.data(), data.size());
        }

        return buffer;
    }

} // namespace Gpu::Ipc
