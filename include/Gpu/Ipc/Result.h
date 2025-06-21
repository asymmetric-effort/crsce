/**
 * @file include/Gpu/Ipc/Result.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <string>

namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::Result
     * @brief Describes the status of a low-level IPC pipe operation (send or recv).
     * @enum Gpu::Ipc::Result
     * @ref docs/Gpu/Design/Gpu-Ipc-Result.md
     *
     * This result type indicates the outcome of pipe communication at the I/O level. It is distinct
     * from higher-level failure codes (`FailureCodes`) which describe the result of GPU task execution.
     *
     * Gpu::Ipc::Result res = ipc.send(message);
     *  if (res != Gpu::Ipc::Result::Success) {
     *      // Handle pipe failure
     *  }
     */
    enum Result : uint8_t {
        Success = 0x00, ///< The pipe operation completed successfully
        Closed = 0x01, ///< The pipe is closed (broken pipe, EOF, etc.)
        IOError = 0x02, ///< A read or write error occurred at the OS level
        InvalidRole = 0x03 ///< An access attempt was made from the wrong process side (parent vs. child)
    };

    /**
     * @name to_string
     * @param result
     * @return std::string
     */
    std::string to_string(const Gpu::Ipc::Result result);
}
