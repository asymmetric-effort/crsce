// file: src/Gpu/Device/Emulator_sync.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

bool Emulator::sync() {
    for (pid_t pid : childPids_) {
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) {
            std::perror("[Emulator] waitpid failed");
            return false;
        }
    }
    childPids_.clear();
    return true;
}

} // namespace Gpu
