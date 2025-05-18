// file: src/Gpu/Device/Emulator_freeBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    bool Emulator::freeBuffer(void* ptr) {
        IpcHeader hdr{CommandType::Free, 0, reinterpret_cast<uint64_t>(ptr)};
        return sendCommand(hdr);
    }

} // namespace Gpu
