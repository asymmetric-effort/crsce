// file: src/Gpu/RuntimeManager/handleWrite.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleWrite(const Ipc::Message& msg, const Common::Buffer8& payload) {
        const bool ok = memory_.write(msg.ptr, payload);
        return {ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::WriteError, 0, {}};
    }

}
