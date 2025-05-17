// file: src/Gpu/Device/Emulator_allocBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    void* Emulator::allocBuffer(std::size_t bytes) {
        IpcHeader hdr{CommandType::Alloc, bytes, 0};
        if (!sendCommand(hdr)) return nullptr;
        void* ptr = nullptr;
        if (!receiveResponse(&ptr, sizeof(ptr))) return nullptr;
        return ptr;
    }

} // namespace Gpu

