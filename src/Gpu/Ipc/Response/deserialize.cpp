/**
 * @file src/Gpu/Ipc/Response/deserialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Response.h"
#include "Gpu/Exceptions/InvalidIpcResponse.h"

namespace Gpu::Ipc {

    void Response::deserialize(const Common::Buffer8& data) {
        if (data.size() < 9)
            throw Exceptions::InvalidIpcResponse("deserialize: buffer too small");

        status_ = static_cast<FailureCodes>(data[0]);

        payload_size_ = 0;
        for (int i = 0; i < 8; ++i)
            payload_size_ |= static_cast<uint64_t>(data[1 + i]) << (i * 8);

        if (data.size() < 9 + payload_size_)
            throw Exceptions::InvalidIpcResponse("deserialize: payload size mismatch");

        this->data_.assign(data.begin() + 9, data.begin() + 9 + payload_size_);
    }

}
