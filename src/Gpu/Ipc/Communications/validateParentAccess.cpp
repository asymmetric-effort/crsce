/**
 * @file src/Gpu/Ipc/Communications/validateParentAccess.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {

    /**
     * @name validateParentAccess
     * @class Communications
     * @public
     * @brief validate the parent can send
     * @return bool
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     */
    bool Communications::validateParentAccess() const {
        return isParent;
    }

}
