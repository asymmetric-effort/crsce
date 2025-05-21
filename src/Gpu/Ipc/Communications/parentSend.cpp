// file: src/Gpu/Ipc/Communications/parentSend.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <errno.h>
#include <cstring>

namespace Gpu::Ipc {

    /**
     * @brief Sends an Message from the parent to the child.
     * @param msg The message to send.
     * @return Result::Success on success, or appropriate error code on failure.
     */
    Result Communications::parentSend(const Message& msg) {
        if (!validateParentAccess()) {
            return Result::Error;
        }

        if (shutdownFlag_.load(std::memory_order_acquire)) {
            return Result::Shutdown;
        }

        const std::vector<uint8_t> buffer = msg.serialize();
        ssize_t written = write(toChildFd_, buffer.data(), buffer.size());

        if (written == static_cast<ssize_t>(buffer.size())) {
            return Result::Success;
        }

        if (written == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return Result::Blocked;
        }

        return Result::Error;
    }

} // namespace Gpu::Ipc
