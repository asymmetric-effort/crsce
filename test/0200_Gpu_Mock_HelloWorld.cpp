// file: test/0200_Gpu_Mock_HelloWorld.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include <iostream>
#include <vector>
#include <cstring>

int main() {
    // Message to round-trip
    const char* msg = "Hello, GPU!";
    std::size_t len = std::strlen(msg) + 1;  // include null terminator

    // Create and initialize GPU (emulator)
    auto gpu = Gpu::Interface::create();
    if (!gpu) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: Failed to create GPU instance.\n";
        return 1;
    }
    if (!gpu->init()) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: GPU initialization failed.\n";
        return 1;
    }

    // Allocate GPU buffer
    void* devPtr = gpu->allocBuffer(len);
    if (!devPtr) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: Buffer allocation failed.\n";
        return 1;
    }

    // Write message to GPU memory
    if (!gpu->writeBuffer(devPtr, msg, len)) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: writeBuffer failed.\n";
        return 1;
    }

    // Read back into host buffer
    std::vector<char> out(len);
    if (!gpu->readBuffer(out.data(), devPtr, len)) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: readBuffer failed.\n";
        return 1;
    }

    // Free GPU buffer
    if (!gpu->freeBuffer(devPtr)) {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Error: freeBuffer failed.\n";
        return 1;
    }

    // Verify round-trip
    if (std::string(out.data()) == msg) {
        std::cout << "[0200_Gpu_Mock_HelloWorld] Round-trip succeeded: " << out.data() << "\n";
        return 0;
    } else {
        std::cerr << "[0200_Gpu_Mock_HelloWorld] Mismatch! got: " << out.data() << "\n";
        return 1;
    }
}
