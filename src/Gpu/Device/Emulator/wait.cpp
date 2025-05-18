// file: src/Gpu/Device/Emulator_wait.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    /**
     * @brief Wait until all previous device commands are completed.
     * @return 0 on success, negative on error.
     * @see docs/Gpu/Abstract/wait.md
     */
    int Emulator::wait() {
        if (isChild_) return -1;
        IpcHeader hdr{ CommandType::Wait, 0, 0, 0 };
        if (!sendCommand(hdr)) return -1;
        // Block until child acknowledges completion
        uint8_t ack = 0;
        if (!receiveResponse(&ack, sizeof(ack))) return -1;
        return 0;
    }

} // namespace Gpu
