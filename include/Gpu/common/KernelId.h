// file: include/Gpu/common/KernelId.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdint>

namespace Gpu {

    enum class KernelId : uint32_t {
        Increment = 1,
        // Future kernels can be added here
    };

} // namespace Gpu
