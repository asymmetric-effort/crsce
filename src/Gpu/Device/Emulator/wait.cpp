// file: src/Gpu/Device/Emulator/wait.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <thread>
#include <chrono>

namespace Gpu::Device {

    bool Emulator::wait(unsigned deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(deadline));
        return true;
    }

}
