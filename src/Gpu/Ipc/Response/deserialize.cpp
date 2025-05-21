// file: src/Gpu/Ipc/Response/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Response.h"
#include <cstring>
#include <stdexcept>

namespace Gpu::Ipc {

    Response Response::deserialize(const uint8_t* buffer, size_t length) {
        if (buffer == nullptr || length < kFixedHeaderSize) {
            throw std::runtime_error("Response::deserialize: insufficient header");
        }

        Response result;
        result.status = buffer[0];
        std::memcpy(&result.size, buffer + 1, sizeof(result.size));

        const size_t totalLength = kFixedHeaderSize + result.size;
        if (length < totalLength) {
            throw std::runtime_error("Response::deserialize: incomplete payload");
        }

        result.data.resize(result.size);
        if (result.size > 0) {
            std::memcpy(result.data.data(), buffer + kFixedHeaderSize, result.size);
        }

        return result;
    }

} // namespace Gpu::Ipc
