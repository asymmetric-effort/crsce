// file: src/Gpu/Ipc/Response/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Response.h"
#include <stdexcept>

namespace Gpu::Ipc {

    Response Response::deserialize(const uint8_t* buffer, std::size_t length) {
        if (length < 9)
            throw std::runtime_error("Response::deserialize(): buffer too small");

        Response out;
        out.status = static_cast<FailureCodes>(buffer[0]);

        out.size = 0;
        for (int i = 0; i < 8; ++i)
            out.size |= static_cast<uint64_t>(buffer[1 + i]) << (i * 8);

        if (length < 9 + out.size)
            throw std::runtime_error("Response::deserialize(): payload size mismatch");

        out.data = Common::Buffer8(buffer + 9, buffer + 9 + out.size);
        return out;
    }

}
