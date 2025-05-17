// file: src/Gpu/Device/Emulator_sendCommand.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::sendCommand(const IpcHeader& hdr, const void* payload) {
        if (!isChild_) {
            if (write(toChildFd_, &hdr, sizeof(hdr)) != sizeof(hdr)) return false;
            if (payload && hdr.size > 0) {
                if (write(toChildFd_, payload, hdr.size) != static_cast<ssize_t>(hdr.size)) return false;
            }
            return true;
        }
        return false;
    }

} // namespace Gpu
