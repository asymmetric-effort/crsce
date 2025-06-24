/**
* @file src/Gpu/Ipc/Communications/recv_Message.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <iostream>
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include <unistd.h>
#include <__ostream/basic_ostream.h>

namespace Gpu::Ipc {

    Result Communications::recv(Message &msg) const {
        constexpr size_t message_size = 24;
        Common::Buffer8 raw(message_size);
        // Select correct pipe: child→parent if parent, else parent→child
        const Handles& fds = isParent ? childToParentFd : parentToChildFd;
        const ssize_t n = read(fds.at(readEndpoint), raw.data(), message_size);

        if (n == static_cast<ssize_t>(message_size)) {
            try {
                msg.deserialize(raw);
                return Result::Success;
            } catch (...) {
                std::cerr << "deserialize failed" << std::endl;
                return Result::IOError;
            }
        }
        return (n == 0 ? Result::Closed : Result::IOError);
    }

}
