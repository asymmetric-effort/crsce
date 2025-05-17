// file: src/Gpu/Device/Emulator_sync.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::sync() {
        if (!isChild_) {
            // Parent waits for emulator
            if (emulatorPid_ > 0) {
                int status;
                waitpid(emulatorPid_, &status, 0);
                emulatorPid_ = -1;
            }
            return true;
        }
        // Child: nothing to sync
        return true;
    }

} // namespace Gpu
