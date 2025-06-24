/**
 * @file src/Gpu/Ipc/Communications/send_Message.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    Result Communications::send(const Message& msg) const {
        // Select correct pipe: parent→child if parent, else child→parent
        const Handles& fds = isParent ? parentToChildFd : childToParentFd;
        const Common::Buffer8 buffer = msg.serialize();
        const ssize_t written = write(fds.at(writeEndpoint), buffer.data(), buffer.size());

        if (written == static_cast<ssize_t>(buffer.size()))
            return Result::Success;
        if (written == 0)
            return Result::Closed;
        return Result::IOError;
    }

}
