// file: test/0100_Gpu_Emulator_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "utils/test/Tester.h"
#include <iostream>
#include <cstring>

int main() {
    Tester tester("test/0100_Gpu_Emulator_init");

    // Create GPU emulator instance
    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu, "Failed to create GPU emulator instance");

    // Initialize emulator (spawns child process)
    bool initOk = gpu->init();
    tester.assertTrue(initOk, "GPU emulator init() failed");
    tester.debug("[0100] init() succeeded. Emulator child running.");

    // Test IPC by allocating a buffer on the emulator
    const char testVal = static_cast<char>(0x5A);
    char* devPtr = static_cast<char*>(gpu->allocBuffer(1));
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    // Write to emulator memory
    char writeVal = testVal;
    bool writeOk = gpu->writeBuffer(devPtr, &writeVal, 1);
    tester.assertTrue(writeOk, "writeBuffer() failed");

    // Read back from emulator memory
    char readVal = 0;
    bool readOk = gpu->readBuffer(&readVal, devPtr, 1);
    tester.assertTrue(readOk, "readBuffer() failed");
    tester.assertTrue(readVal == testVal, "Round-trip value mismatch");
    tester.debug(std::format("IPC round-trip succeeded: 0x{:X}", static_cast<int>(readVal)));

    // Free the buffer
    bool freeOk = gpu->freeBuffer(devPtr);
    tester.assertTrue(freeOk, "freeBuffer() failed");

    // Shutdown and sync
    bool syncOk = gpu->sync();
    tester.assertTrue(syncOk, "sync() failed");
    tester.debug("sync() succeeded. Emulator child terminated.");

    return 0;
}
