/**
 * @file src/Gpu/KernelManager/get.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include "Gpu/Exceptions/KernelNotFound.h"
#include <stdexcept>

namespace Gpu {

    const Common::Buffer8& KernelManager::get(const Common::KernelId id) const {
        std::lock_guard lock(mutex_);
        const auto it = table_.find(id);
        if (it == table_.end()) {
            throw Gpu::Exceptions::KernelNotFound("ID " + std::to_string(id));
        }
        return it->second;
    }

}
