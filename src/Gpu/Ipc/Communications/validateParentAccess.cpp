/**
 * @file src/Gpu/Ipc/Communications/validateParentAccess.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

namespace Gpu::Ipc {

    bool Communications::validateParentAccess() const {
        return isParent;
    }

}
