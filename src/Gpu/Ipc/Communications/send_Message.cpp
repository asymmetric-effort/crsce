// file: src/Gpu/Ipc/Communications/send_Message.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    Result Communications::send(const Message& msg) {
        if (!validateParentAccess()) return Result::InvalidRole;

        auto buffer = msg.serialize();
        ssize_t written = write(parentToChildFd[1], buffer.data(), buffer.size());
        if (written == static_cast<ssize_t>(buffer.size())) return Result::Success;
        if (written == 0) return Result::Closed;
        return Result::IOError;
    }

}
