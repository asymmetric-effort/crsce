/**
 * @file src/Gpu/Ipc/MemoryTracker/clear.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    void MemoryTracker::clear() {
        std::lock_guard lock(mutex_);
        table_.clear();
    }

}
