// file: src/Gpu/Device/childProcessLoop_handleLaunchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void Emulator::handleWait(const int fromChildFd_) {
        constexpr char ack = 0;
        write(fromChildFd_, &ack, 1);
    }

} // namespace Gpu
