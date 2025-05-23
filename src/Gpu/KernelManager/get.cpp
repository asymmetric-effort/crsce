// file: src/Gpu/KernelManager/get.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/KernelManager.h"
#include <stdexcept>

namespace Gpu {

    const Common::Buffer8& KernelManager::get(const KernelId id) const {
        std::lock_guard lock(mutex_);
        const auto it = table_.find(id);
        if (it == table_.end()) {
            throw Exceptions::KernelNotFound("ID " + std::to_string(id));
        }
        return it->second;
    }

}
