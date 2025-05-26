/**
 * @file src/Gpu/Ipc/Communications/recv_Response.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <algorithm>

namespace Gpu::Ipc {

    Result Communications::recv(Response& res) const {
        if (!validateParentAccess()) return Result::InvalidRole;

        uint8_t header[9] = {};
        if (const ssize_t read_header = read(childToParentFd[readEndpoint], header, 9); read_header != 9)
            return (read_header == 0 ? Result::Closed : Result::IOError);

        uint64_t payload_size = 0;
        for (int i = 0; i < 8; ++i)
            payload_size |= static_cast<uint64_t>(header[1 + i]) << (i * 8);

        Common::Buffer8 full(9 + payload_size);
        std::copy_n(header, 9, full.begin());

        if (payload_size > 0) {
            if (const ssize_t read_payload = read(childToParentFd[readEndpoint], full.data() + 9, payload_size); read_payload != static_cast<ssize_t>(payload_size))
                return (read_payload == 0 ? Result::Closed : Result::IOError);
        }

        try {
            res.deserialize(full);
            return Result::Success;
        } catch (...) {
            return Result::IOError;
        }
    }

}
