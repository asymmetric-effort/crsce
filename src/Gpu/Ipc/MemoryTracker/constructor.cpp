/**
 * @file src/Gpu/Ipc/MemoryTracker/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/MemoryTracker.h"
#include <random>

namespace Gpu::Ipc {

    MemoryTracker::MemoryTracker() {
        std::random_device rd;
        prng_ = std::mt19937_64(rd());
    }

}
