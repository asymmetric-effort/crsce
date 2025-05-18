// file: src/Gpu/Device/Emulator_writeBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::writeBuffer(void* dst, const void* src, std::size_t bytes) {
        IpcHeader hdr{
            CommandType::Write,
            0,                                // kernelId unused for write
            static_cast<uint64_t>(bytes),    // size
            reinterpret_cast<uint64_t>(dst)  // ptr = device address
        };
        return sendCommand(hdr, src);
    }

} // namespace Gpu

