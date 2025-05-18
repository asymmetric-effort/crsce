// file: include/Gpu/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/common/KernelId.h"
#include <cstddef>
#include <cstdint>
#include <memory>

namespace Gpu {

/// Abstract GPU interface supporting multiple backends (Emulator, CUDA, ROCm, Metal)
class Interface {
public:
    virtual ~Interface() = default;

    /// Initialize the GPU device or emulator
    virtual bool init() = 0;

    /// Allocate device memory
    virtual void* allocBuffer(std::size_t bytes) = 0;
    /// Free device memory
    virtual bool freeBuffer(void* ptr) = 0;

    /// Copy data from host to device
    virtual bool writeBuffer(void* dst, const void* src, std::size_t bytes) = 0;
    /// Copy data from device to host
    virtual bool readBuffer(void* dst, const void* src, std::size_t bytes) = 0;

    /// Dispatch a named kernel on the device
    virtual bool launchKernel(KernelId id, void* buffer, std::size_t count) = 0;

    /**
     * @brief Block until all previously dispatched commands finish.
     * @see docs/Gpu/Abstract/wait.md
     * @return 0 on success, non-zero error code on failure.
     */
    virtual int wait() = 0;

    /**
     * @brief Reset the device context, releasing all resources.
     * @see docs/Gpu/Abstract/reset.md for details on cross-backend behavior.
     */
    virtual void reset() = 0;

    /// Factory to create the default (Emulator) implementation
    static std::unique_ptr<Interface> create();
};

} // namespace Gpu
