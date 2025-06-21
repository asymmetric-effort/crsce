/**
 * @file src/Gpu/Ipc/Communications/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

namespace Gpu::Ipc {

    Communications::Communications(const Handles parentToChild, const Handles childToParent, const bool isParentProcess)
        : isParent(isParentProcess) {
        parentToChildFd[0] = parentToChild[0];
        parentToChildFd[1] = parentToChild[1];
        childToParentFd[0] = childToParent[0];
        childToParentFd[1] = childToParent[1];
    }

}
