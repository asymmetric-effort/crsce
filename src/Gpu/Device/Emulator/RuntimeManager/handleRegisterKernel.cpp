/**
 * @file src/Gpu/RuntimeManager/handleRegisterKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name handleRegisterKernel
     * @class RuntimeManager
     * @public
     * @brief Handle kernel registration request.
     * @param msg IPC message specifying kernel ID.
     * @param blob Binary blob containing compiled kernel code.
     * @return Response indicating success or failure of registration.
     */
    Ipc::Response RuntimeManager::handleRegisterKernel(const Ipc::Message& msg, const Common::Buffer8& blob) {
        const bool ok = kernels_.registerKernel(msg.kernelId, blob);
        return {ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::KernelNotFound, 0, {}};
    }

}
