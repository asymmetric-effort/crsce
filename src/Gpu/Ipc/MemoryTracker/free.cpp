/**
 * @file src/Gpu/Ipc/MemoryTracker/free.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    bool MemoryTracker::free(Common::AbstractPtr ptr) {
        std::lock_guard lock(mutex_);
        return table_.erase(ptr) > 0;
    }

}
