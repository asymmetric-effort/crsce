// file: src/Gpu/Device/receiveResponse.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::receiveResponse(void* payload, size_t size) {
        if (!isChild_) {
            if (read(fromChildFd_, payload, size) != static_cast<ssize_t>(size)) return false;
            return true;
        }
        return false;
    }

} // namespace Gpu
