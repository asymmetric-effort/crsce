// file: src/Gpu/Device/wait.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/common/IpcResponseMsg.h"
#include <unistd.h>

namespace Gpu {

    int Emulator::wait() {
        constexpr IpcHeader hdr{
            CommandType::Wait,
            0,      // kernelId not used
            0,      // size = 0
            0       // ptr = 0
        };

        if (!sendCommand(hdr)) return -1;

        try {
            const IpcResponseMsg msg = receiveResponseMsg();
            return (msg.status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
        } catch (...) {
            return EXIT_FAILURE;
        }
    }

} // namespace Gpu
