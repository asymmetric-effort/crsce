/**
 * @file src/Gpu/RuntimeManager/isShutdown.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name isShutdown
     * @class RuntimeManager
     * @public
     * @brief Query whether shutdown has been initiated.
     * @return true if shutdown has been requested, false otherwise.
     */
    bool RuntimeManager::isShutdown() const {
        return shutdown_;
    }

}
