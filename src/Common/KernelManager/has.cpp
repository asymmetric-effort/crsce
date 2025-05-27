/**
 * @file src/Gpu/KernelManager/has.cpp
 * @brief Define the KernelManager methods
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
/**
 * @namespace Common
 * @brief A common CRSCE namespace for reusable generic functionality.
 */
namespace Common {
    /**
     * @name has
     * @class KernelManager
     * @brief Return true if KernelManager has a record with the given KernelId value.
     * @param id Common::KernelId
     * @return bool
     */
    bool KernelManager::has(const Common::KernelId id) const {
        std::lock_guard lock(mutex_);
        return table_.contains(id);
    }

}
