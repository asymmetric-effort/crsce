// file: src/Gpu/Device/Emulator_reset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    /**
     * @brief Reset the emulator by terminating the child process and cleaning up.
     * @see docs/Gpu/Abstract/reset.md
     */
    void Emulator::reset() {
        if (!isChild_) {
            IpcHeader hdr{ CommandType::Reset, 0, 0, 0 };
            sendCommand(hdr);
            if (emulatorPid_ > 0) {
                int status = 0;
                waitpid(emulatorPid_, &status, 0);
            }
            if (toChildFd_ >= 0) close(toChildFd_);
            if (fromChildFd_ >= 0) close(fromChildFd_);
        }
    }

} // namespace Gpu
