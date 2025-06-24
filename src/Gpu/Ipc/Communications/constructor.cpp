/**
 * @file src/Gpu/Ipc/Communications/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

namespace Gpu::Ipc {
    Communications::Communications(const Handles parentToChild, const Handles childToParent, const bool isParentProcess)
        : parentToChildFd(parentToChild),childToParentFd(childToParent),isParent(isParentProcess) {
        /*noop*/
    }
}
