// file: test/0300_Gpu_Mock_UseThreads.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "Gpu/common/KernelId.h"
#include "utils/test/Tester.h"
#include <vector>
#include <string>

int main() {
    Tester tester("test/0300_Gpu_Mock_UseThreads");

    // 1) Create and initialize GPU emulator Backend
    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu.get(), "Failed to create GPU emulator instance");
    tester.assertTrue(gpu->init(), "GPU emulator init() failed");
    tester.debug("Emulator initialized");

    // 2) Prepare host buffer of zeros
    const size_t count = 8;
    std::vector<int> hostBuf(count, 0);

    // 3) Allocate device buffer and copy zeros
    void* devPtr = gpu->allocBuffer(count * sizeof(int));
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");
    tester.assertTrue(
        gpu->writeBuffer(devPtr, hostBuf.data(), count * sizeof(int)),
        "writeBuffer() failed"
    );
    tester.debug("Initial data uploaded to device");

    // 4) Dispatch multiple independent increment kernels
    const int numTasks = 4;
    for (int i = 0; i < numTasks; ++i) {
        bool launched = gpu->launchKernel(
            Gpu::KernelId::Increment,
            devPtr,
            count
        );
        tester.assertTrue(launched, "launchKernel() failed");
    }
    tester.debug("Launched increment kernels");

    // ** Read back results before shutdown and sync **
    tester.assertTrue(
        gpu->readBuffer(hostBuf.data(), devPtr, count * sizeof(int)),
        "readBuffer() failed"
    );
    tester.debug("Device results read back to host");

    // 5) Verify each element == numTasks (zero + numTasks increments)
    for (size_t i = 0; i < count; ++i) {
        tester.assertEqual(
            hostBuf[i],
            numTasks,
            "Element at index " + std::to_string(i) + " incorrect"
        );
    }
    tester.debug("All elements incremented correctly (" + std::to_string(numTasks) + ")");

    // 6) Shutdown and sync
    tester.assertTrue(gpu->sync(), "sync() failed");
    tester.debug("sync() succeeded");

    // 7) Cleanup
    tester.assertTrue(gpu->freeBuffer(devPtr), "freeBuffer() failed");

    tester.debug("Test complete");
    return 0;
}
