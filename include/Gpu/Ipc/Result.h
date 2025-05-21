// file: include/Gpu/Ipc/Result.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include <cstdint>

namespace Gpu::Ipc {

    /**
     * @enum Result
     * @brief Status codes returned by IPC send/receive operations.
     *
     * This enum describes the result of an interprocess communication operation
     * between GPU emulator parent and child processes. Each value conveys an
     * exact outcome:
     *
     * - Success: The operation completed successfully.
     * - Empty: No message was available to read (non-blocking context).
     * - Blocked: The pipe was full or the receiver was unable to receive.
     * - Shutdown: Sending is disallowed due to active shutdown.
     * - Error: An unrecoverable or system-level error occurred.
     */
    enum class Result : uint8_t {
        Success = 0,   ///< Operation completed successfully
        Empty = 1,     ///< No message in queue to read
        Blocked = 2,   ///< Receiver is not ready or pipe is full
        Shutdown = 3,  ///< IPC channel is shut down
        Error = 4      ///< System-level or internal error
    };

} // namespace Gpu::Ipc
