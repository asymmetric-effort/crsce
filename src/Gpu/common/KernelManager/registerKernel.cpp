/**
 * @file src/Gpu/KernelManager/registerKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <random>

namespace Gpu {

    bool KernelManager::registerKernel(const Common::KernelId id, const Common::Buffer8& binary) {
        std::lock_guard lock(mutex_);
        table_[id] = binary;
        return true;
    }

}
