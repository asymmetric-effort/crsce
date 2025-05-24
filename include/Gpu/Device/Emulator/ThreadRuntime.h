// file: include/Gpu/ThreadRuntime.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Common/Buffer8.h"

namespace Gpu {

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
