// file: src/Gpu/Device/reset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <sys/wait.h>
#include <unistd.h>

namespace Gpu {

    /**
     * @see docs/Gpu/Abstract/reset.md
     */
    void Emulator::reset() {
        // Send shutdown command to child
        IpcHeader hdr{ CommandType::Reset,
                       0,  // kernelId unused
                       0,  // size unused
                       0   // ptr unused
        };
        sendCommand(hdr);

        // Wait for child process to exit
        if (emulatorPid_ > 0) {
            int status = 0;
            waitpid(emulatorPid_, &status, 0);
        }

        // Close IPC file descriptors
        if (toChildFd_ >= 0) close(toChildFd_);
        if (fromChildFd_ >= 0) close(fromChildFd_);
    }

} // namespace Gpu
