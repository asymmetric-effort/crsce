/**
 * @file src/Gpu/RuntimeManager/handleReset.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name handleReset
     * @class RuntimeManager
     * @public
     * @brief Handle a reset request, reinitializing internal state.
     * @return Response indicating reset completion status.
     */
    Ipc::Response RuntimeManager::handleReset() {
        threads_.joinAll();
        memory_.clear();
        kernels_.clear();
        return {Ipc::FailureCodes::Success, 0, {}};
    }

}
