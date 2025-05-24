// file: src/Gpu/RuntimeManager/handleRead.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "../../../include/Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu {

    Ipc::Response RuntimeManager::handleRead(const Ipc::Message& msg) {
        Common::Buffer8 buffer(msg.size);
        const bool ok = memory_.read(msg.ptr, buffer);
        return {
            ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::ReadError,
            ok ? static_cast<uint64_t>(buffer.size()) : 0,
            ok ? std::move(buffer) : Common::Buffer8{}
        };
    }

}
