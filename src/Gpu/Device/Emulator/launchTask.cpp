/**
 * @file src/Gpu/Device/Emulator/launchTask.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/IpcRecvFailed.h"
#include "Gpu/Exceptions/IpcSendFailed.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name launchTask
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Launch a registered GPU kernel with provided arguments.
     * @param id Kernel identifier to launch.
     * @param args Argument buffer to pass to the kernel.
     * @return true if kernel launch succeeded, false otherwise.
     */
    bool Emulator::launchTask(const KernelId id, const Common::Buffer8& args) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::launchTask() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::LaunchTask;
        msg.kernelId = static_cast<uint32_t>(id);
        msg.size = args.size();

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed(result);
        }
        if (const auto result = ipc_->send(Ipc::Response{Ipc::FailureCodes::Success, msg.size, args}); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcSendFailed(result);
        }

        Ipc::Response res;
        if (const auto result = ipc_->recv(res); result != Ipc::Result::Success) {
            throw Gpu::Exceptions::IpcRecvFailed(result);
        }

        return res.status == Ipc::FailureCodes::Success;
    }

}
