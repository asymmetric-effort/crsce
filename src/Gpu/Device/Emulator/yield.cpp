// file: src/Gpu/Device/Emulator/yield.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <thread>

namespace Gpu::Device {

    bool Emulator::yield() {
        std::this_thread::yield();
        return true;
    }

}
