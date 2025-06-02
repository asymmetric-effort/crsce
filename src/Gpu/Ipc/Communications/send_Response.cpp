/**
 * @file src/Gpu/Ipc/Communications/send_Response.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {

    /**
     * @name send (Response)
     * @class Communications
     * @brief send IPC Response from child to parent
     * @param res
     * @return Gpu::Ipc::Result
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     */
    Result Communications::send(const Response& res) const {
        if (!validateChildAccess()) return Result::InvalidRole;

        const auto buffer = res.serialize();
        const ssize_t written = write(childToParentFd[writeEndpoint], buffer.data(), buffer.size());
        if (written == static_cast<ssize_t>(buffer.size())) return Result::Success;
        if (written == 0) return Result::Closed;
        return Result::IOError;
    }

}
