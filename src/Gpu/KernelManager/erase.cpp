// file: src/Gpu/KernelManager/erase.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "../../../include/Gpu/Common/KernelManager.h"
#include <random>

namespace Gpu {

    bool KernelManager::erase(const KernelId id) {
        std::lock_guard lock(mutex_);
        if (const auto it = table_.find(id); it != table_.end()) {
            std::ranges::generate(it->second, std::rand);
            table_.erase(it);
            return true;
        }
        return false;
    }

}
