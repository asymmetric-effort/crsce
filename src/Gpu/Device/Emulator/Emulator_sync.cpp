// file: src/Gpu/Device/Emulator.cpp (sync method update)
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::sync() {
        if (!isChild_) {
            // Parent: send shutdown command to child emulator
            IpcHeader shutdownHdr{CommandType::Shutdown, 0, 0};
            if (!sendCommand(shutdownHdr)) {
                std::cerr << "[Emulator] sync: failed to send Shutdown command\n";
            }
            // Wait for emulator child to exit
            if (emulatorPid_ > 0) {
                int status = 0;
                if (waitpid(emulatorPid_, &status, 0) < 0) {
                    std::perror("[Emulator] sync: waitpid failed");
                    return false;
                }
                emulatorPid_ = -1;
            }
            // Close IPC fds
            if (toChildFd_ >= 0) close(toChildFd_);
            if (fromChildFd_ >= 0) close(fromChildFd_);
            return true;
        }
        // Child: no-op, loop in childProcessLoop handles exit
        return true;
    }

} // namespace Gpu
