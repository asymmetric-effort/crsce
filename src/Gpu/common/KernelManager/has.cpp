/**
 * @file src/Gpu/KernelManager/has.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"

namespace Gpu {

    bool KernelManager::has(const Common::KernelId id) const {
        std::lock_guard lock(mutex_);
        return table_.contains(id);
    }

}
