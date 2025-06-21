/**
 * @file src/Gpu/KernelManager/clear.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <algorithm>
#include <random>
#include <ranges>

namespace Gpu {

    bool KernelManager::clear() {
        std::lock_guard lock(mutex_);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::uint8_t> dist(0, 255);
        for (auto &blob : table_ | std::views::values)
            // ReSharper disable once CppUseRangeAlgorithm
            std::generate(blob.begin(), blob.end(), [&] { return dist(gen); });
        table_.clear();
        return true;
    }

}
