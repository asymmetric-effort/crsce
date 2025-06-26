/**
 * @file src/Gpu/RuntimeManager/handleRead.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleRead(const Ipc::Message::Base& msg) const {
        // Common::Buffer8 buffer(msg.size());
        // const bool ok = memory_.read(msg.ptr(), buffer);
        return {
            // ok ? Ipc::FailureCodes::IpcSuccess : Ipc::FailureCodes::ReadError,
            // ok ? buffer.size() : 0,
            // ok ? std::move(buffer) : Common::Buffer8{}
        };
    }

}
