// file: src/Gpu/KernelManager/clear.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/KernelManager.h"
#include <random>
#include <ranges>

namespace Gpu {

    bool KernelManager::clear() {
        std::lock_guard lock(mutex_);
        for (auto &blob: table_ | std::views::values)
            std::ranges::generate(blob, std::rand);
        table_.clear();
        return true;
    }

}
