/**
 * @file src/Gpu/Device/Emulator/write_Buffer8.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    bool Emulator::write(const Common::Buffer8& source, Common::AbstractPtr& dst) {
        if (!initialized_)
            throw Exceptions::DeviceNotReady("Emulator::write(Buffer8) called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Write;
        msg.ptr = dst;
        msg.size = source.size();

        ipc_->send(msg);
        ipc_->send(Ipc::Response{Ipc::FailureCodes::IpcSuccess, msg.size, source});  // Payload trick

        Ipc::Response res;
        ipc_->recv(res);

        return res.status == Ipc::FailureCodes::IpcSuccess;
    }

}
