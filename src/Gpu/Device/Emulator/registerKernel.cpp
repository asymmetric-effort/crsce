/**
 * @file src/Gpu/Device/Emulator/registerKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    bool Emulator::registerKernel(const KernelId id, const Common::Buffer8& binary) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::registerKernel() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::RegisterKernel;
        msg.kernelId = static_cast<uint32_t>(id);
        msg.size = binary.size();

        ipc_->send(msg);
        ipc_->send(Ipc::Response{Ipc::FailureCodes::Success, msg.size, binary});

        Ipc::Response res;
        ipc_->recv(res);

        return res.status == Ipc::FailureCodes::Success;
    }

}
