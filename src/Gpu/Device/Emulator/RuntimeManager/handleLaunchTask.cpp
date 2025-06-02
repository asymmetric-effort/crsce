/**
 * @file src/Gpu/RuntimeManager/handleLaunchTask.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"
#include "Gpu/Device/Emulator/ThreadRuntime.h"
#include <thread>

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name handleLaunchTask
     * @class RuntimeManager
     * @public
     * @brief Handle a kernel launch request.
     * @param msg IPC message specifying kernel ID and launch parameters.
     * @param args Argument buffer for the kernel.
     * @return Response indicating success or failure of launch.
     */
    Ipc::Response RuntimeManager::handleLaunchTask(const Ipc::Message& msg, const Common::Buffer8& args) {
        if (!kernels_.has(msg.kernelId))
            return {Ipc::FailureCodes::KernelNotFound, 0, {}};

        const auto& blob = kernels_.get(msg.kernelId);
        try {
            threads_.insert(static_cast<uint32_t>(msg.kernelId),
                std::thread([blob, args] {
                    const ThreadRuntime rt(blob, args);
                    rt.run();
                }));
            return {Ipc::FailureCodes::Success, 0, {}};
        } catch (...) {
            return {Ipc::FailureCodes::ThreadLaunchFailure, 0, {}};
        }
    }

}
