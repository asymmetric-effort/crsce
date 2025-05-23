// file: src/Gpu/Ipc/MemoryTracker/write.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    bool MemoryTracker::write(Common::AbstractPtr dst, const Common::Buffer8& src) {
        std::lock_guard lock(mutex_);
        auto it = table_.find(dst);
        if (it == table_.end() || it->second.size() != src.size()) return false;
        it->second = src;
        return true;
    }

}
