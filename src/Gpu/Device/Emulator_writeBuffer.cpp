// file: src/Gpu/Device/Emulator_writeBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::writeBuffer(void* dst, const void* src, std::size_t bytes) {
        IpcHeader hdr{CommandType::Write, bytes, reinterpret_cast<uint64_t>(dst)};
        if (!sendCommand(hdr, src)) return false;
        return true;
    }

} // namespace Gpu
