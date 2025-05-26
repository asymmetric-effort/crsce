/**
 * @file include/Gpu/ThreadRuntime.h
 * @brief Declare the runtime wrapper for Gpu::Device::Emulator which will facilitate execution of user-defined
 *        Gpu kernel blobs.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"

namespace Gpu::Device {

    /**
     * @name Gpu::ThreadRuntime
     * @brief Simulates GPU kernel execution using a binary blob.
     * @ref docs/Gpu/Design/Gpu-ThreadRuntime.md
     */
    class ThreadRuntime {
    public:
        explicit ThreadRuntime(const Common::Buffer8& kernelBlob, const Common::Buffer8& args = {});
        void run() const;  ///< Execute the kernel blob in a deterministic, thread-local manner.

    private:
        const Common::Buffer8& kernel_;
        const Common::Buffer8& args_;
    };

} // namespace Gpu
