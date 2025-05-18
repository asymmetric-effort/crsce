// file: src/Gpu/Kernels/IncrementKernel.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Kernels/IncrementKernel.h"
#include <cstdint>

namespace Gpu {

    void IncrementKernel::run(void* buffer, std::size_t count) {
        int* data = static_cast<int*>(buffer);
        for (std::size_t i = 0; i < count; ++i) {
            data[i] += 1;
        }
    }

} // namespace Gpu
