// file: src/Gpu/RuntimeManager/isShutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/RuntimeManager.h"

namespace Gpu::Device {

    bool RuntimeManager::isShutdown() const {
        return shutdown_;
    }

}
