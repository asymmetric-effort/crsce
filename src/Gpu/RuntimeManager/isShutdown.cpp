// file: src/Gpu/RuntimeManager/isShutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/RuntimeManager.h"

namespace Gpu {

    bool RuntimeManager::isShutdown() const {
        return shutdown_;
    }

}
