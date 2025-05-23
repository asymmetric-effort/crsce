// file: src/Gpu/Ipc/MemoryTracker/generateUniqueHandle.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    Common::AbstractPtr MemoryTracker::generateUniqueHandle() {
        Common::AbstractPtr ptr = 0;
        std::lock_guard lock(mutex_);
        do {
            ptr = prng_();
        } while (ptr == 0 || table_.contains(ptr));
        return ptr;
    }

}
