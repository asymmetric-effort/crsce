// file: src/Gpu/Ipc/Communications/childSend.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <errno.h>

namespace Gpu::Ipc {

    /**
     * @brief Sends an Response from the child to the parent.
     * @param response The response message to send.
     * @return Result::Success on success, or appropriate error code on failure.
     */
    Result Communications::childSend(const Response& response) {
        if (!validateChildAccess()) {
            return Result::Error;
        }

        if (shutdownFlag_.load(std::memory_order_acquire)) {
            return Result::Shutdown;
        }

        const std::vector<uint8_t> buffer = response.serialize();
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
