// file: src/Gpu/Device/Emulator/memfence.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu::Device {

    bool Emulator::memfence() {
        return true; // No memory reordering at emulation level
    }

}
