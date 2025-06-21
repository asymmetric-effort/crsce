/**
 * @file src/Gpu/KernelManager/erase.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <algorithm>
#include <cstdlib>
#include <random>

namespace Gpu {
    bool KernelManager::erase(const Common::KernelId id) {
        std::lock_guard lock(mutex_);
        if (const auto it = table_.find(id); it != table_.end()) {
            // ReSharper disable once CppUseRangeAlgorithm
            std::generate(it->second.begin(), it->second.end(), [] { return std::rand(); });
            table_.erase(it);
            return true;
        }
        return false;
    }
}
