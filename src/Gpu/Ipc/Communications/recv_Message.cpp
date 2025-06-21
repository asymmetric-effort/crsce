/**
* @file src/Gpu/Ipc/Communications/recv_Message.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include <unistd.h>

namespace Gpu::Ipc {
    Result Communications::recv(Message &msg) const {
        if (!validateChildAccess()) return Result::InvalidRole;

        constexpr size_t message_size = 24;
        Common::Buffer8 raw{message_size, 0};

        const ssize_t n = read(parentToChildFd.at(0), raw.data(), message_size);

        if (n == static_cast<ssize_t>(message_size)) {
            try {
                msg.deserialize(raw);
                return Result::Success;
            } catch (...) {
                return Result::IOError;
            }
        }

        if (n == 0) return Result::Closed;
        return Result::IOError;
    }
}
