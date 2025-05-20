// file: src/Gpu/Device/receiveResponse.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::receiveResponse(void* payload, size_t size) {
        if (!isChild_) {
            char status = 1;
            if (read(fromChildFd_, &status, 1) != 1 || status != 0) return false;
            if (size > 0 && payload)
                return read(fromChildFd_, payload, size) == static_cast<ssize_t>(size);
            return true;
        }
        return false;
    }

} // namespace Gpu
