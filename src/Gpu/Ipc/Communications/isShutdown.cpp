/**
 * @file src/Gpu/Ipc/Communications/send_Response.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {

    /**
     * @name isShutdown
     * @class Communications
     * @public
     * @brief return whether or not the class instance is in shutdown
     * @return bool
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     * @return
     */
    [[nodiscard]] bool Communications::isShutdown() const noexcept {
        return shutdownFlag.load();
    };
}
