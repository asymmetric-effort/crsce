/**
 * @file src/Gpu/RuntimeManager/handleShutdown.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name handleShutdown
     * @class RuntimeManager
     * @public
     * @brief Handle a shutdown request, marking runtime for termination.
     * @return Response indicating shutdown completion.
     */
    Ipc::Response RuntimeManager::handleShutdown() {
        shutdown_ = true;
        threads_.joinAll();
        memory_.clear();
        kernels_.clear();
        return {Ipc::FailureCodes::Success, 0, {}};
    }

}
