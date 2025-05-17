// file: test/0100_Gpu_Mock_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include <cassert>
#include <iostream>

int main() {
    auto gpu = Gpu::Interface::create();
    assert(gpu && "[0100_Gpu_Mock_init] Failed to create Emulator instance");

    bool initialized = gpu->init();
    assert(initialized && "[0100_Gpu_Mock_init] Emulator initialization failed");
    std::cout << "[0100_Gpu_Mock_init] Emulator init test passed.\n";
    return 0;
}
