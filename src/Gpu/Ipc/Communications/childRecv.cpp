// file: src/Gpu/Ipc/Communications/childRecv.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <vector>
#include <errno.h>
#include <cstring>

namespace Gpu::Ipc {

    /**
     * @brief Receives an Message in the child from the parent.
     * @param msg Output parameter for the received message.
     * @return Result::Success if message is received, or appropriate error.
     */
    Result Communications::childRecv(Message& msg) {
        if (!validateChildAccess()) {
            return Result::Error;
        }

        if (shutdownFlag_.load(std::memory_order_acquire)) {
            return Result::Shutdown;
        }

        uint8_t headerBuffer[Message::kFixedHeaderSize] = {};
        ssize_t hdrBytes = read(fromChildFd_, headerBuffer, sizeof(headerBuffer));
        if (hdrBytes == 0) {
            return Result::Empty; // EOF or no data
        }
        if (hdrBytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return Result::Empty;
            }
            return Result::Error;
        }

        // Determine full payload size from header
        size_t fullLength = Message::requiredLength(headerBuffer, hdrBytes);
        std::vector<uint8_t> fullBuffer(fullLength);
        std::memcpy(fullBuffer.data(), headerBuffer, hdrBytes);

        ssize_t remaining = fullLength - hdrBytes;
        ssize_t readTotal = 0;
        while (readTotal < remaining) {
            ssize_t r = read(fromChildFd_, fullBuffer.data() + hdrBytes + readTotal, remaining - readTotal);
            if (r <= 0) return Result::Error;
            readTotal += r;
        }

        try {
            msg = Message::deserialize(fullBuffer.data(), fullLength);
            return Result::Success;
        } catch (...) {
            return Result::Error;
        }
    }

} // namespace Gpu::Ipc
