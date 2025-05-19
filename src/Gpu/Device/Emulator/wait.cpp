// file: src/Gpu/Device/Emulator_wait.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    int Emulator::wait() {
        IpcHeader hdr;
        hdr.type = CommandType::Wait;
        hdr.size = 0;
        hdr.ptr = 0;

        if (!sendCommand(hdr)) return false;

        char ack;
        return receiveResponse(&ack, 1);
    }

}
