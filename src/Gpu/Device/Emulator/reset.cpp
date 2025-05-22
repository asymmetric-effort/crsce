// file: src/Gpu/Device/Emulator/reset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Device {

    void Emulator::reset() {
        if (!comm_ || !initialized_) return;

        Ipc::Message msg;
        msg.type     = 0x07; // CommandType::Reset
        msg.kernelId = 0;
        msg.size     = 0;
        msg.ptr      = 0;

        if (comm_->parentSend(msg) != Ipc::Result::Success) return;

        Ipc::Response resp;
        if (comm_->parentRecv(resp) != Ipc::Result::Success) return;

        if (resp.status == 0) {
            tracker_.clear();
        }
    }

} // namespace Gpu::Device
