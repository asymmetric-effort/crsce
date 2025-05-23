// file: include/Gpu/Ipc/FailureCodes.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <cstdint>

namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::FailureCodes
     * @brief Describes the response status code of an IPC operation encoded as uint8_t
     * @enum Gpu::Ipc::FailureCodes
     * @ref docs/Gpu/Design/Gpu-Ipc-FailureCodes.md
     * @example
     *   Gpu::Ipc::FailureCodes status = Gpu::Ipc::FailureCodes::ReadError;
     *       if (status != Gpu::Ipc::FailureCodes::Success) {
     *          // handle error
     *       }
     */
    enum class FailureCodes : uint8_t {
        Success = 0x00,
        UnknownError = 0x01,
        InvalidPointer = 0x02,
        AllocationFailed = 0x03,
        WriteError = 0x04,
        ReadError = 0x05,
        KernelNotFound = 0x06,
        ThreadLaunchFailure = 0x07,
        ResetFailure = 0x08,
        ShutdownFailure = 0x09
    };

}

