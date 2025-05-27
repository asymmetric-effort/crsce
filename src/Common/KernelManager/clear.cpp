/**
 * @file src/Gpu/KernelManager/clear.cpp
 * @brief Define the KernelManager methods
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <random>
#include <ranges>
/**
 * @namespace Common
 * @brief A common CRSCE namespace for reusable generic functionality.
 */
namespace Common {
    /**
     * @name clear
     * @class KernelManager
     * @brief Lock and clear the contents of the KernelManager.
     * @return bool (success=true, failure=false)
     */
    bool KernelManager::clear() {
        std::lock_guard lock(mutex_);
        for (auto &blob: table_ | std::views::values)
            std::ranges::generate(blob, std::rand);
        table_.clear();
        return true;
    }

}
