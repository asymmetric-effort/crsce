/**
 * @file src/Gpu/RuntimeManager/handleRegisterKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleRegisterKernel(const Ipc::Message& msg, const Common::Buffer8& blob) {
        const bool ok = kernels_.registerKernel(msg.kernelId, blob);
        return {ok ? Ipc::FailureCodes::IpcSuccess : Ipc::FailureCodes::KernelNotFound, 0, {}};
    }

}
