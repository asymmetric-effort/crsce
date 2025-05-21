// file: src/Gpu/Ipc/Communications/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <stdexcept>

namespace Gpu::Ipc {

    Communications::Communications(const pid_t childPid)
        : childPid_(childPid),
          isParent_(getpid() != 0 && getpid() != childPid),
          shutdownFlag_(false)
    {
        if (pipe(toChild_) == -1 || pipe(fromChild_) == -1) {
            throw std::runtime_error("Failed to create IPC pipes");
        }

        if (isParent_) {
            parentPid_   = getpid();
            toChildFd_   = toChild_[1];    // Parent writes
            fromChildFd_ = fromChild_[0];  // Parent reads
        } else {
            parentPid_   = childPid_;      // In child, this is parent’s PID
            toChildFd_   = toChild_[0];    // Child reads
            fromChildFd_ = fromChild_[1];  // Child writes
        }
    }

} // namespace Gpu::Ipc
