/**
 * @file src/Gpu/Ipc/Communications/send_Message.cpp
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
     * @name send (Message)
     * @class Communications
     * @brief send IPC Message from parent to child
     * @param msg
     * @return Gpu::Ipc::Result
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     */
    Result Communications::send(const Message& msg) const {
        if (!validateParentAccess())
            return Result::InvalidRole;

        const Common::Buffer8 buffer = msg.serialize();

        const ssize_t written = write(parentToChildFd[1], buffer.data(), buffer.size());

        if (written == static_cast<ssize_t>(buffer.size()))
            return Result::Success;

        if (written == 0)
            return Result::Closed;

        return Result::IOError;
    }

}
