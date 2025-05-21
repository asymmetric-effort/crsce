// file: src/Gpu/Ipc/Communications/parentRecv.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <vector>
#include <errno.h>
#include <cstring>

namespace Gpu::Ipc {

    /**
     * @brief Receives an Response from the child in the parent process.
     * @param response Output parameter for the received response.
     * @return Result::Success if a complete message is received; appropriate Result otherwise.
     */
    Result Communications::parentRecv(Response& response) {
        if (!validateParentAccess()) {
            return Result::Error;
        }

        if (shutdownFlag_.load(std::memory_order_acquire)) {
            return Result::Shutdown;
        }

        uint8_t fixedHeader[Response::kFixedHeaderSize] = {};
        ssize_t hdrBytes = read(fromChildFd_, fixedHeader, sizeof(fixedHeader));
        if (hdrBytes == 0) {
            return Result::Empty;
        }
        if (hdrBytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return Result::Empty;
            }
            return Result::Error;
        }

        // Determine payload length from header
        size_t fullLength = Response::requiredLength(fixedHeader, hdrBytes);
        std::vector<uint8_t> fullBuffer(fullLength);
        std::memcpy(fullBuffer.data(), fixedHeader, hdrBytes);

        ssize_t remaining = fullLength - hdrBytes;
        ssize_t readTotal = 0;
        while (readTotal < remaining) {
            ssize_t r = read(fromChildFd_, fullBuffer.data() + hdrBytes + readTotal, remaining - readTotal);
            if (r <= 0) return Result::Error;
            readTotal += r;
        }

        try {
            response = Response::deserialize(fullBuffer.data(), fullLength);
            return Result::Success;
        } catch (...) {
            return Result::Error;
        }
    }

} // namespace Gpu::Ipc
