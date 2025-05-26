/**
 * @file src/Gpu/Device/Emulator/launchTask.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    bool Emulator::launchTask(const KernelId id, const Common::Buffer8& args) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::launchTask() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::LaunchTask;
        msg.kernelId = static_cast<uint32_t>(id);
        msg.size = args.size();

        ipc_->send(msg);
        ipc_->send(Ipc::Response{Ipc::FailureCodes::Success, msg.size, args});

        Ipc::Response res;
        ipc_->recv(res);

        return res.status == Ipc::FailureCodes::Success;
    }

}
