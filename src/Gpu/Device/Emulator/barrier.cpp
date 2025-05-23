// file: src/Gpu/Device/Emulator/barrier.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu::Device {

    bool Emulator::barrier() {
        return true; // No-op for software simulator
    }

}
