// file: test/0300_Gpu_Mock_UseThreads.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include "utils/test/Tester.h"
#include <cstring>
#include <iostream>
#include <vector>

int main() {
    Tester tester("test/0300_Gpu_Mock_UseThreads");

    // Create and initialize GPU emulator
    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu.get(), "Failed to create GPU emulator instance");
    tester.assertTrue(gpu->init(), "GPU emulator init() failed");
    tester.debug("Emulator initialized");

    // Prepare test data: a buffer of 5 integers
    const size_t count = 5;
    std::vector<int> hostBuf(count, 0);
    void* devPtr = gpu->allocBuffer(count * sizeof(int));
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    // Send to GPU
    tester.assertTrue(gpu->writeBuffer(devPtr, hostBuf.data(), count * sizeof(int)), "writeBuffer() failed");

    // Define an increment "kernel" as a lambda.  This is the payload the emulator will execute.
    auto incrementKernel = [devPtr, count]() {
        int* data = static_cast<int*>(devPtr);
        for (size_t i = 0; i < count; ++i) {
            data[i] += 1;
        }
    };

    // Launch the kernel via the generic task API
    bool launched = gpu->launchTask(incrementKernel);
    tester.assertTrue(launched, "launchTask(incrementKernel) failed");
    tester.debug("Increment kernel dispatched");

    // Sync and read back
    tester.assertTrue(gpu->sync(), "sync() failed");
    tester.debug("sync() succeeded; tasks complete");

    tester.assertTrue(gpu->readBuffer(hostBuf.data(), devPtr, count * sizeof(int)), "readBuffer() failed");

    // Verify each element was incremented exactly once
    for (size_t i = 0; i < count; ++i) {
        tester.assertEqual(hostBuf[i], 1, "Element not incremented");
    }
    tester.debug("All elements incremented correctly");

    // Cleanup
    tester.assertTrue(gpu->freeBuffer(devPtr), "freeBuffer() failed");
    tester.assertTrue(gpu->sync(), "final sync() failed");
    tester.debug("Test complete");

    return 0;
}
