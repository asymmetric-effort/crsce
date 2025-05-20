// file: src/Gpu/Device/childProcessLoop_handleLaunchTask.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    namespace Cpl {

        void handleWait(int fromChildFd_) {
            char ack = 0;
            write(fromChildFd_, &ack, 1);
        }

    } // namespace Cpl

} // namespace Gpu
