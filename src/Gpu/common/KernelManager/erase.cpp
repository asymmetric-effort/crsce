/**
 * @file src/Gpu/KernelManager/erase.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <algorithm>
#include <random>
#include <ranges>

namespace Gpu {
    bool KernelManager::erase(const Common::KernelId id) {
        std::lock_guard lock(mutex_);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::uint8_t> dist(0, 255);

        if (const auto it = table_.find(id); it != table_.end()) {
            std::ranges::generate(it->second, [&] { return dist(gen); });
            table_.erase(it);
            return true;
        }
        return false;
    }
}
