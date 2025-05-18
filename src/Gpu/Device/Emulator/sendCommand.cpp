// file: src/Gpu/Device/sendCommand.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::sendCommand(const IpcHeader& hdr, const void* payload) {
        std::cout << "[Emulator::sendCommand] sending command..." << std::endl;
        if (!isChild_) {
            if (write(toChildFd_, &hdr, sizeof(hdr)) != sizeof(hdr)) return false;
            if (payload && hdr.size > 0) {
                if (write(toChildFd_, payload, hdr.size) != static_cast<ssize_t>(hdr.size)) return false;
            }
            std::cout << "[Emulator::sendCommand] isChild:true" << std::endl;
            return true;
        }
        std::cout << "[Emulator::sendCommand] not child" << std::endl;
        return false;
    }

} // namespace Gpu
