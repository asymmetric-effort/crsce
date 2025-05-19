// file: src/Gpu/Device/shutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void Emulator::shutdown() {
        IpcHeader hdr{};
        hdr.type = CommandType::Shutdown;
        hdr.size = 0;
        hdr.ptr = 0;
        childActive_ = false;
        sendCommand(hdr);
        waitpid(emulatorPid_, nullptr, 0);  // Wait for child to exit
    }

} //namespace Gpu
