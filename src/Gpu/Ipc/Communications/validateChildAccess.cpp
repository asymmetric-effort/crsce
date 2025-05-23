// file: src/Gpu/Ipc/Communications/validateChildAccess.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"

namespace Gpu::Ipc {

    bool Communications::validateChildAccess() const {
        return !isParent;
    }

}
