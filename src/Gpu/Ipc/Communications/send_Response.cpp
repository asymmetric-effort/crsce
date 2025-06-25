/**
 * @file src/Gpu/Ipc/Communications/send_Response.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {
    Result Communications::send(const Response &res) const {
        const auto buffer = res.serialize();
        const ssize_t written = write(responsePipe.at(writeEndpoint), buffer.data(), buffer.size());
        if (written == static_cast<ssize_t>(buffer.size()))
            return Result::Success;
        if (written == 0)
            return Result::Closed;
        return Result::IOError;
    }
}
