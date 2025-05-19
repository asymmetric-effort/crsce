// file: test/0300_Gpu_Emulator_UseThreads.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "Gpu/common/KernelId.h"
#include "utils/test/Tester.h"
#include <vector>

int main() {
    Tester tester("test/0300_Gpu_Emulator_UseThreads", TerminateOnError);
    tester.deadline(/*default 60s*/);
    tester.skip("disabled for debugging");

    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu.get(), "Failed to create GPU emulator instance");
    tester.assertTrue(gpu->init(), "GPU emulator init() failed");
    tester.debug("Emulator initialized");

    const size_t count = 8;
    std::vector<int> hostBuf(count, 0);
    void* devPtr = gpu->allocBuffer(count * sizeof(int));
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    tester.assertTrue(
        gpu->writeBuffer(devPtr, hostBuf.data(), count * sizeof(int)),
        "writeBuffer() failed"
    );
    tester.debug("Initial data uploaded to device");

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

    tester.assertTrue(gpu->wait(), "wait() failed");
    tester.debug("wait() succeeded");

    tester.assertTrue(
        gpu->readBuffer(hostBuf.data(), devPtr, count * sizeof(int)),
        "readBuffer() failed"
    );
    tester.debug("Device results read back to host");

    for (size_t i = 0; i < count; ++i) {
        tester.assertEqual(
            hostBuf[i],
            numTasks,
            "Element at index " + std::to_string(i) + " incorrect"
        );
    }
    tester.debug("All elements incremented correctly (" + std::to_string(numTasks) + ")");

    tester.assertTrue(gpu->freeBuffer(devPtr), "freeBuffer() failed");
    tester.assertTrue(gpu->wait(), "final wait() failed");
    tester.debug("Test complete");

    return 0;
}
