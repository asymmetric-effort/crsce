// file: src/Gpu/Ipc/Communications/validateChildAccess.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    /**
     * @brief Checks whether the current process is the designated child.
     * @return true if current PID does not match parent, and matches child role.
     */
    bool Communications::validateChildAccess() const noexcept {
        return !isParent_ && getpid() != parentPid_;
    }

} // namespace Gpu::Ipc
