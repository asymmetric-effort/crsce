// file: src/Gpu/Ipc/MemoryTracker/read.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/MemoryTracker.h"

namespace Gpu::Ipc {

    bool MemoryTracker::read(Common::AbstractPtr src, Common::Buffer8& dst) const {
        std::lock_guard lock(mutex_);
        auto it = table_.find(src);
        if (it == table_.end() || it->second.size() != dst.size()) return false;
        dst = it->second;
        return true;
    }

}
