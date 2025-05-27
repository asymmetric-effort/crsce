/**
 * @file src/Gpu/KernelManager/get.cpp
 * @brief Define the KernelManager methods
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Common/KernelManager.h"
#include "Gpu/Exceptions/KernelNotFound.h"
#include <stdexcept>
/**
 * @namespace Common
 * @brief A common CRSCE namespace for reusable generic functionality.
 */
namespace Common {
    /**
     * @name get
     * @class KernelManager
     * @brief Retrieve a Kernel binary blob given its KernelId
     * @param id Common::KernelId
     * @return Common::Buffer8
     */
    const Common::Buffer8& KernelManager::get(const Common::KernelId id) const {
        std::lock_guard lock(mutex_);
        const auto it = table_.find(id);
        if (it == table_.end()) {
            throw Gpu::Exceptions::KernelNotFound("ID:" + std::to_string(id));
        }
        return it->second;
    }

}
