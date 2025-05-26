/**
 * @file src/Gpu/RuntimeManager/handleFree.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleFree(const Ipc::Message& msg) {
        const bool ok = memory_.free(msg.ptr);
        return {ok ? Ipc::FailureCodes::Success : Ipc::FailureCodes::InvalidPointer, 0, {}};
    }

}
