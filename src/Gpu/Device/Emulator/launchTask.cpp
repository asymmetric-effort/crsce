// file: src/Gpu/Device/Emulator/launchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

namespace Gpu::Device {

    bool Emulator::launchTask(uint32_t kernelId, const std::vector<uint8_t>& args) {
        if (!comm_ || !initialized_) return false;

        Ipc::Message msg;
        msg.type     = 0x06; // CommandType::LaunchTask
        msg.kernelId = kernelId;
        msg.size     = static_cast<uint64_t>(args.size());
        msg.ptr      = 0;

        if (comm_->parentSend(msg) != Ipc::Result::Success) return false;

        if (!args.empty()) {
            if (comm_->parentSend(args) != Ipc::Result::Success) return false;
        }

        Ipc::Response resp;
        if (comm_->parentRecv(resp) != Ipc::Result::Success) return false;
        return resp.status == 0;
    }

} // namespace Gpu::Device
