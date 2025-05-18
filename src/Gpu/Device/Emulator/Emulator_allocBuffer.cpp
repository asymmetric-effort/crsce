// file: src/Gpu/Device/Emulator_allocBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    void* Emulator::allocBuffer(std::size_t bytes) {
        IpcHeader hdr{
            CommandType::Alloc,
            0,                             // kernelId unused for alloc
            static_cast<uint64_t>(bytes), // size
            0                              // ptr unused for alloc
        };
        if (!sendCommand(hdr)) return nullptr;
        void* ptr = nullptr;
        receiveResponse(&ptr, sizeof(ptr));
        return ptr;
    }

} // namespace Gpu
