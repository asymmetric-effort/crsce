// file: src/Gpu/Ipc/Communications/recv_Message.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    Result Communications::recv(Message& msg) {
        if (!validateChildAccess()) return Result::InvalidRole;

        uint8_t buffer[24] = {};
        ssize_t read_bytes = read(parentToChildFd[0], buffer, 24);
        if (read_bytes == 24) {
            msg = Message::deserialize(buffer, 24);
            return Result::Success;
        }
        if (read_bytes == 0) return Result::Closed;
        return Result::IOError;
    }

}
