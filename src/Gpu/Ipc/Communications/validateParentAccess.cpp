// file: src/Gpu/Ipc/Communications/validateParentAccess.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Communications.h"
#include <unistd.h>

namespace Gpu::Ipc {

    /**
     * @brief Checks whether the current process is the designated parent.
     * @return true if current PID matches stored parent PID, false otherwise.
     */
    bool Communications::validateParentAccess() const noexcept {
        return isParent_ && getpid() == parentPid_;
    }

} // namespace Gpu::Ipc
