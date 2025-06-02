/**
 * @file include/Gpu/ThreadRuntime.h
 * @brief Declare the runtime wrapper for Gpu::Device::Emulator which will facilitate execution of user-defined
 *        Gpu kernel blobs.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Common/Buffer8.h"
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name Gpu::ThreadRuntime
     * @class ThreadRuntime
     * @brief Simulates GPU kernel execution using a binary blob.
     * @ref docs/Gpu/Design/Gpu-ThreadRuntime.md
     */
    class ThreadRuntime {
    public:
        /**
         * @name constructor
         * @class ThreadRuntime
         * @brief initialize the class
         * @param kernelBlob Common::Buffer8 - kernel binary blob
         * @param args Common::Buffer8 - serialized binary arguments for binary
         */
        explicit ThreadRuntime(const Common::Buffer8 &kernelBlob, const Common::Buffer8 &args = {});

        /**
         * @name run
         * @class ThreadRuntime
         * @brief Execute the kernel blob in a deterministic, thread-local manner.
         */
        void run() const;

    private:
        /**
         * @property kernel_
         * @private
         * @brief kernel binary blob
         */
        const Common::Buffer8 &kernel_;
        /**
         * @property args_
         * @private
         * @brief serialized binary arguments for kernel binary
         */
        const Common::Buffer8 &args_;
    };
} // namespace Gpu
