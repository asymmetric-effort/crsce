/**
 * @file src/Gpu/RuntimeManager/handleLaunchTask.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"
#include "Gpu/Device/Emulator/ThreadRuntime.h"
#include <thread>

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleLaunchTask(const Ipc::Message::Base& msg, const Common::Buffer8& args) {
        // if (!kernels_.has(msg.kernelId()))
            // return {Ipc::FailureCodes::KernelNotFound, 0, {}};

        // const auto& blob = kernels_.get(msg.kernelId());
        try {
            // threads_.insert(msg.kernelId(),
                // std::jthread([blob, args] {
                    // const ThreadRuntime rt(blob, args);
                    // rt.run();
                // }));
            return {Ipc::FailureCodes::IpcSuccess, 0, {}};
        } catch (...) {
            return {Ipc::FailureCodes::ThreadLaunchFailure, 0, {}};
        }
    }

}
