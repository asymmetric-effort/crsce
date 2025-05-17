// file: src/Gpu/Device/Emulator.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "Gpu/Device/Emulator.h"

namespace Gpu {

    Emulator::~Emulator() {
        std::cout << "[Emulator] teardown successful." << std::endl;
        sync();
    }

} // namespace Gpu
