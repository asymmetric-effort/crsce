// file: src/Gpu/Device/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    Emulator::~Emulator() {
        std::cout << "[Emulator] teardown started." << std::endl;
        if (!isChild_ && emulatorPid_ > 0) {
            // Send shutdown command
            IpcHeader hdr{CommandType::Reset,0,0};
            sendCommand(hdr);
            // Wait for child to exit
            int status;
            waitpid(emulatorPid_, &status, 0);
        }
        std::cout << "[Emulator] teardown successful." << std::endl;
    }
} // namespace Gpu
