/**
 * @file src/Gpu/KernelManager/registerKernel.cpp
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
     * @name registerKernel
     * @class KernelManager
     * @brief Given a kernel binary (blob) using Common::Buffer8 and a KernelId), create an entry to store and
     *        track the binary.
     * @param id Common::KernelId
     * @param binary Common::Buffer8
     * @return bool (success=true, failure=false)
     */
    bool KernelManager::registerKernel(const Common::KernelId id, const Common::Buffer8& binary) {
        std::lock_guard lock(mutex_);
        table_[id] = binary;
        return true;
    }

}
