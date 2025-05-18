// file: src/Gpu/Device/Emulator_wait.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <sys/wait.h>
#include <unistd.h>

namespace Gpu {

    /**
     * @see docs/Gpu/Abstract/wait.md
     */
    int Emulator::wait() {
        if (isChild_) return -1;
        IpcHeader hdr{ CommandType::Wait, 0, 0, 0 };
        if (!sendCommand(hdr)) return -1;
        // Wait for acknowledgement (0 bytes)
        // reuse receiveResponse for zero-sized read
        if (!receiveResponse(nullptr, 0)) return -1;
        return 0;
    }

} // namespace Gpu
