/**
 * @file src/Gpu/Device/Emulator/registerKernel.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device
{
    bool Emulator::registerKernel(const KernelId id, const Common::Buffer8& binary)
    {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::registerKernel() called before init()");

        Ipc::Message msg;
        msg.type(Ipc::MessageType::RegisterKernel);
        msg.kernelId(static_cast<uint32_t>(id));
        msg.size(binary.size());

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success) return false;
        if (const auto result = ipc_->send(Ipc::Response{Ipc::FailureCodes::IpcSuccess, msg.size(), binary}); result !=
            Ipc::Result::Success)
            return false;

        Ipc::Response res;
        ipc_->recv(res);

        return res.status() == Ipc::FailureCodes::IpcSuccess;
    }
}
