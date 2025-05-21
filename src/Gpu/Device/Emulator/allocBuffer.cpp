// file: src/Gpu/Device/allocBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void* Emulator::allocBuffer(std::size_t bytes) {
        const IpcHeader hdr{
            CommandType::Alloc,
            0,  // kernelId not used
            static_cast<uint64_t>(bytes),
            0
        };

        if (!sendCommand(hdr)) return nullptr;

        try {
            const IpcResponseMsg msg = receiveResponseMsg();
            if (msg.status != 0 || msg.size < sizeof(void*)) return nullptr;

            return msg.as<void*>();

        } catch (...) {
            return nullptr;
        }
    }

} // namespace Gpu
