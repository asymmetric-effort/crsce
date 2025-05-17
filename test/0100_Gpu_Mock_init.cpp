// file: test/0100_Gpu_Mock_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    // Create GPU emulator instance
    auto gpu = Gpu::Interface::create();
    assert(gpu && "[test/0100_Gpu_Mock_init] Failed to create GPU emulator instance");

    // Initialize emulator (spawns child process)
    bool initOk = gpu->init();
    assert(initOk && "GPU emulator init() failed");
    std::cout << "[test/0100_Gpu_Mock_init] init() succeeded. Emulator child running.\n";

    // Test IPC by allocating a buffer on the emulator
    const char testVal = 0x5A;
    char* devPtr = static_cast<char*>(gpu->allocBuffer(1));
    assert(devPtr && "[test/0100_Gpu_Mock_init] allocBuffer() returned nullptr");

    // Write to emulator memory
    char writeVal = testVal;
    bool writeOk = gpu->writeBuffer(devPtr, &writeVal, 1);
    assert(writeOk && "[test/0100_Gpu_Mock_init] writeBuffer() failed");

    // Read back from emulator memory
    char readVal = 0;
    bool readOk = gpu->readBuffer(&readVal, devPtr, 1);
    assert(readOk && "[test/0100_Gpu_Mock_init] readBuffer() failed");
    assert(readVal == testVal && "Round-trip value mismatch");
    std::cout << "[test/0100_Gpu_Mock_init] IPC round-trip succeeded: 0x"
              << std::hex << static_cast<int>(readVal) << std::dec << "\n";

    // Free the buffer
    bool freeOk = gpu->freeBuffer(devPtr);
    assert(freeOk && "[test/0100_Gpu_Mock_init] freeBuffer() failed");

    // Shutdown and sync
    bool syncOk = gpu->sync();
    assert(syncOk && "sync() failed");
    std::cout << "[test/0100_Gpu_Mock_init] sync() succeeded. Emulator child terminated.\n";

    return 0;
}
