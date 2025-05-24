// file: src/Gpu/RuntimeManager/handleAlloc.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "../../../include/Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu {

    Ipc::Response RuntimeManager::handleAlloc(const Ipc::Message& msg) {
        const auto ptr = memory_.alloc(static_cast<std::size_t>(msg.size));
        Ipc::Response res;
        res.status = (ptr != 0) ? Ipc::FailureCodes::Success : Ipc::FailureCodes::AllocationFailed;
        res.size = sizeof(Common::AbstractPtr);
        res.data.resize(sizeof(Common::AbstractPtr));
        for (int i = 0; i < 8; ++i)
            res.data[i] = static_cast<uint8_t>((ptr >> (i * 8)) & 0xFF);
        return res;
    }

}
