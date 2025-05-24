// file: src/Gpu/KernelManager/has.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "../../../include/Gpu/Common/KernelManager.h"

namespace Gpu {

    bool KernelManager::has(const KernelId id) const {
        std::lock_guard lock(mutex_);
        return table_.contains(id);
    }

}
