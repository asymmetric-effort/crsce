// file: src/Gpu/RuntimeManager/handleReset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    Ipc::Response RuntimeManager::handleReset() {
        threads_.joinAll();
        memory_.clear();
        kernels_.clear();
        return {Ipc::FailureCodes::Success, 0, {}};
    }

}
