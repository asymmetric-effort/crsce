// file: src/Gpu/Device/Emulator_freeBuffer.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    bool Emulator::freeBuffer(void* ptr) {
        if (!ptr) return false;
        std::free(ptr);
        return true;
    }

} // namespace Gpu
