/**
 * @file src/Gpu/Device/Emulator/free.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    bool Emulator::free(Common::AbstractPtr& ptr) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::free() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Free;
        msg.ptr = ptr;

        ipc_->send(msg);

        Ipc::Response res;
        ipc_->recv(res);

        return res.status == Ipc::FailureCodes::IpcSuccess;
    }

}
