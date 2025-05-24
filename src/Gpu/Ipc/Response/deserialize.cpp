// file: src/Gpu/Ipc/Response/deserialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Response.h"
#include "Gpu/Exceptions/InvalidIpcResponse.h"

namespace Gpu::Ipc {

    void Response::deserialize(const Common::Buffer8& data) {
        if (data.size() < 9)
            throw Exceptions::InvalidIpcResponse("deserialize: buffer too small");

        status = static_cast<FailureCodes>(data[0]);

        size = 0;
        for (int i = 0; i < 8; ++i)
            size |= static_cast<uint64_t>(data[1 + i]) << (i * 8);

        if (data.size() < 9 + size)
            throw Exceptions::InvalidIpcResponse("deserialize: payload size mismatch");

        this->data.assign(data.begin() + 9, data.begin() + 9 + size);
    }

}
