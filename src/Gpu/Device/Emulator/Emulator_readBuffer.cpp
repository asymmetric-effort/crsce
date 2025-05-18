// file: src/Gpu/Device/Emulator_readBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::readBuffer(void* dst, const void* src, std::size_t bytes) {
        IpcHeader hdr{
            CommandType::Read,
            0,                                // kernelId unused for read
            static_cast<uint64_t>(bytes),    // size
            reinterpret_cast<uint64_t>(src)  // ptr = device address
        };
        if (!sendCommand(hdr)) return false;
        return receiveResponse(dst, bytes);
    }

} // namespace Gpu

