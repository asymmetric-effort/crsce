/**
 * @file src/Gpu/ThreadRegistry/empty.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/ThreadRegistry.h"
/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name empty
     * @class ThreadRegistry
     * @public
     * @brief Checks if the registry is empty.
     * @return bool
     */
    bool ThreadRegistry::empty() const {

        std::lock_guard lock(mutex_);

        return table_.empty();

    }

}
