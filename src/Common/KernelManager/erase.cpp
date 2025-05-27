/**
 * @file src/Gpu/KernelManager/erase.cpp
 * @brief Define the KernelManager methods
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include <random>
/**
 * @namespace Common
 * @brief A common CRSCE namespace for reusable generic functionality.
 */
namespace Common {
    /**
     * @name erase
     * @class KernelManager
     * @brief Erase a given record from the KernelManager
     * @param id Common::KernelId
     * @return bool (success=true, failure=false)
     */
    bool KernelManager::erase(const Common::KernelId id) {
        std::lock_guard lock(mutex_);
        if (const auto it = table_.find(id); it != table_.end()) {
            std::ranges::generate(it->second, std::rand);
            table_.erase(it);
            return true;
        }
        return false;
    }

}
