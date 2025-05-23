// file: src/Gpu/Ipc/Communications/recv_Response.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    Result Communications::recv(Response& res) {
        if (!validateParentAccess()) return Result::InvalidRole;

        uint8_t header[9] = {};
        ssize_t read_header = read(childToParentFd[0], header, 9);
        if (read_header != 9) return (read_header == 0 ? Result::Closed : Result::IOError);

        uint64_t payload_size = 0;
        for (int i = 0; i < 8; ++i)
            payload_size |= static_cast<uint64_t>(header[1 + i]) << (i * 8);

        std::vector<uint8_t> full(9 + payload_size);
        std::copy(header, header + 9, full.begin());

        if (payload_size > 0) {
            ssize_t read_payload = read(childToParentFd[0], full.data() + 9, payload_size);
            if (read_payload != static_cast<ssize_t>(payload_size))
                return (read_payload == 0 ? Result::Closed : Result::IOError);
        }

        res = Response::deserialize(full.data(), full.size());
        return Result::Success;
    }

}
