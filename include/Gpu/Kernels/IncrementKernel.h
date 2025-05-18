// file: include/Gpu/Kernels/IncrementKernel.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Kernel.h"

namespace Gpu {

    /// Generic "Increment" kernel implementation usable by any backend
    tclass IncrementKernel : public Kernel {
        public:
        void run(void* buffer, std::size_t count) override;
    };

} // namespace Gpu
