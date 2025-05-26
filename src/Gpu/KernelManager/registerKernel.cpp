/**
 * @file src/Gpu/KernelManager/registerKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "../../../include/Gpu/Common/KernelManager.h"
#include <random>

namespace Gpu {

    bool KernelManager::registerKernel(const KernelId id, const Common::Buffer8& binary) {
        std::lock_guard lock(mutex_);
        table_[id] = binary;
        return true;
    }

}
