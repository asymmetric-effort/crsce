// file: src/Gpu/RuntimeManager/handleShutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "../../../include/Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu {

    Ipc::Response RuntimeManager::handleShutdown() {
        shutdown_ = true;
        threads_.joinAll();
        memory_.clear();
        kernels_.clear();
        return {Ipc::FailureCodes::Success, 0, {}};
    }

}
