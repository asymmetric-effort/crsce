/**
 * @file src/Gpu/Ipc/Communications/recv_Message.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <vector>

namespace Gpu::Ipc {

    Result Communications::recv(Message& msg) const {
        if (!validateChildAccess()) return Result::InvalidRole;

        uint8_t raw[24] = {};
        const ssize_t n = read(parentToChildFd[0], raw, 24);

        if (n == 24) {
            try {
                const Common::Buffer8 buffer(raw, raw + 24);
                msg.deserialize(buffer);
                return Result::Success;
            } catch (...) {
                return Result::IOError;
            }
        }

        if (n == 0) return Result::Closed;
        return Result::IOError;
    }

}
