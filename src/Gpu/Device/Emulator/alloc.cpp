/**
 * @file src/Gpu/Device/Emulator/alloc.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

namespace Gpu::Device {

    Common::AbstractPtr Emulator::alloc(const std::size_t bytes) {
        if (!initialized_) throw Exceptions::DeviceNotReady("Emulator::alloc() called before init()");

        Ipc::Message msg;
        msg.type = Ipc::CommandType::Alloc;
        msg.size = bytes;

        if (const auto result = ipc_->send(msg);result!=Ipc::Result::Success)
            return 0;


        Ipc::Response res;
        if (const auto result = ipc_->recv(res);result!=Ipc::Result::Success)
            return 0;

        if (res.status != Ipc::FailureCodes::Success || res.size != sizeof(Common::AbstractPtr)) return 0;

        Common::AbstractPtr ptr = 0;
        for (int i = 0; i < 8; ++i)
            ptr |= static_cast<uint64_t>(res.data[i]) << (i * 8);

        return ptr;
    }

}
