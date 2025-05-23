// file: src/Gpu/Device/Emulator/reset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    void Emulator::reset() {
        if (!initialized_) return;

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Reset;
        ipc_->send(msg);
    }

}
