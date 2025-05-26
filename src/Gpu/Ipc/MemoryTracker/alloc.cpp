/**
 * @file src/Gpu/Ipc/MemoryTracker/alloc.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    Common::AbstractPtr MemoryTracker::alloc(std::size_t size) {
        if (size == 0) return 0;
        Common::Buffer8 buffer(size, 0);
        Common::AbstractPtr ptr = generateUniqueHandle();
        std::lock_guard lock(mutex_);
        table_[ptr] = std::move(buffer);
        return ptr;
    }

}
