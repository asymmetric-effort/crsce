// file: src/Gpu/Device/Emulator/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <sys/wait.h>
#include <unistd.h>

namespace Gpu::Device {

    Emulator::~Emulator() {
        shutdown();
    }

}
