// file: include/Gpu/Kernel.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/common/KernelId.h"
#include <cstddef>

namespace Gpu {

    /// Base class for all kernels; each backend registers concrete Kernel implementations
    class Kernel {
    public:
        virtual ~Kernel() = default;
        /// Execute kernel logic on the given device pointer and element count
        virtual void run(void* buffer, std::size_t count) = 0;
    };

} // namespace Gpu
