/**
 * @file src/Gpu/Device/Emulator/read_Buffer8.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    bool Emulator::read(Common::Buffer8& source, Common::AbstractPtr& dst) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::read(Buffer8) called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Read;
        msg.ptr = dst;
        msg.size = source.size();

        ipc_->send(msg);

        Ipc::Response res;
        ipc_->recv(res);

        if (res.status != Ipc::FailureCodes::IpcSuccess || res.size != source.size())
            return false;

        source = res.data;
        return true;
    }

}
