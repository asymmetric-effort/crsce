// file: test/0100_Gpu_Emulator_init.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "utils/test/Tester.h"
#include <iostream>
#include <cstring>

int main() {
    Tester tester("test/0110_Gpu_Emulator_init", TerminateOnError);
    tester.deadline(30);

    // Create GPU emulator instance
    const auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu, "Failed to create GPU emulator instance");

    // Initialize emulator (spawns child process)
    const bool initOk = gpu->init();
    tester.assertTrue(initOk, "GPU emulator init() failed");

    // Test IPC by allocating a buffer on the emulator
    const auto devPtr = gpu->allocBuffer(1);
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    // Write to emulator memory
    constexpr char testVal = static_cast<char>(0x5A);
    constexpr char writeVal = testVal;
    const bool writeOk = gpu->writeBuffer(devPtr, &writeVal, 1);
    tester.assertTrue(writeOk, "writeBuffer() failed");

    // Read back from emulator memory
    char readVal = 0;
    const bool readOk = gpu->readBuffer(&readVal, devPtr, 1);
    tester.assertTrue(readOk, "readBuffer() failed");
    tester.assertEqual(readVal, testVal, "Round-trip value mismatch");
    tester.debug(std::format("IPC round-trip succeeded: 0x{:X}", static_cast<int>(readVal)));

    // Free the buffer
    const bool freeOk = gpu->freeBuffer(devPtr);
    tester.assertTrue(freeOk, "freeBuffer() failed");

    // Shutdown and wait
    tester.debug("Waiting on threads");
    const bool waitOk = gpu->wait();
    tester.assertTrue(waitOk==EXIT_SUCCESS, "wait() failed");
    tester.debug("wait() succeeded. Emulator child terminated.");

    return 0;
}
