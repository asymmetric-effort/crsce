/**
 * @file src/Gpu/Device/Emulator/reset.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Exceptions/IpcSendFailed.h"

namespace Gpu::Device
{
    void Emulator::reset()
    {
        if (!initialized_) return;

        Ipc::Message msg;
        msg.type(Ipc::MessageType::Reset);

        if (const auto result = ipc_->send(msg); result != Ipc::Result::Success)
            throw Gpu::Exceptions::IpcSendFailed("Emulator::reset message send failed");
    }
}
