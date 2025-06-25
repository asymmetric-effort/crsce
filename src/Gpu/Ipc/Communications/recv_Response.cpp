/**
 * @file src/Gpu/Ipc/Communications/recv_Response.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <algorithm>

namespace Gpu::Ipc {
    Result Communications::recv(Response &res) const {
        constexpr size_t header_size = 9;

        Common::Buffer8 header{header_size, 0};
        if (const ssize_t read_header = read(responsePipe.at(readEndpoint), header.data(), header.size());
            read_header != header.size())
            return (read_header == 0 ? Result::Closed : Result::IOError);

        uint64_t payload_size = 0;
        // Decode 64-bit little-endian payload size from header[1..8]
        for (int i = 0; i < 8; ++i)
            // cppcheck-suppress containerOutOfBounds
            payload_size |= static_cast<uint64_t>(header.at(1 + i)) << (i * 8);


        if (constexpr size_t MAX_MESSAGE_SIZE = 1048576; payload_size > MAX_MESSAGE_SIZE) return Result::IOError;

        Common::Buffer8 full(header.size() + payload_size, 0);
        std::copy_n(header.data(), header.size(), full.begin());

        if (payload_size > 0) {
            if (const ssize_t read_payload = read(responsePipe.at(readEndpoint), full.data() + header.size(),
                                                  payload_size); read_payload != static_cast<ssize_t>(payload_size))
                return (read_payload == 0 ? Result::Closed : Result::IOError);
        }

        if (full.size() < header_size + payload_size) return Result::IOError;

        try {
            res.deserialize(full);
            return Result::Success;
        } catch (...) {
            return Result::IOError;
        }
    }
}
