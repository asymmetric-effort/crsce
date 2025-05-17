// file: test/0100_Gpu_Mock_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include <cassert>
#include <iostream>

int main() {
#ifdef GPU_EMULATOR
    auto gpu = Gpu::Interface::create();
    assert(gpu && "Failed to create Emulator instance");

    bool initialized = gpu->init();
    assert(initialized && "Emulator initialization failed");
    std::cout << "Emulator init test passed.\n";
    return 0;
#else
    std::cerr << "Error: GPU_EMULATOR flag not defined. Skipping test.\n";
    return 1;
#endif
}
