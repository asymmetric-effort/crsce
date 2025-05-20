// file: test/0140_Gpu_Emulator_Reset.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "Gpu/common/KernelId.h"
#include "utils/test/Tester.h"
#include <vector>

int main() {
    Tester tester("test/0140_Gpu_Emulator_Reset", TerminateOnError);
    tester.deadline(60);

    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu.get(), "Failed to create GPU emulator instance");
    tester.assertTrue(gpu->init(), "GPU emulator init() failed");

    const size_t count = 4;
    std::vector<int> hostBuf(count, 1);  // initialize to 1s
    void* devPtr = gpu->allocBuffer(count * sizeof(int));
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    tester.assertTrue(
        gpu->writeBuffer(devPtr, hostBuf.data(), count * sizeof(int)),
        "writeBuffer() failed"
    );

    gpu->reset();

    // Post-reset: buffer should no longer be valid
    std::vector<int> zeroBuf(count, 0);

    // Undefined GPU behavior should always be handled safely by our abstraction layer.
    tester.assertFalse(
        gpu->readBuffer(hostBuf.data(), devPtr, count * sizeof(int)),
        "readBuffer() unexpectedly succeeded after reset"
    );

    // Post-reset: new buffer should be allocatable and usable
    void* newDevPtr = gpu->allocBuffer(count * sizeof(int));
    tester.assertNotNull(newDevPtr, "allocBuffer() after reset returned nullptr");

    tester.assertTrue(
        gpu->writeBuffer(newDevPtr, zeroBuf.data(), count * sizeof(int)),
        "writeBuffer() after reset failed"
    );

    tester.assertTrue(
        gpu->launchKernel(Gpu::KernelId::Increment, newDevPtr, count),
        "launchKernel() after reset failed"
    );

    tester.assertTrue(gpu->wait(), "wait() after reset failed");

    tester.assertTrue(
        gpu->readBuffer(hostBuf.data(), newDevPtr, count * sizeof(int)),
        "readBuffer() after relaunch failed"
    );

    for (size_t i = 0; i < count; ++i) {
        tester.assertEqual(
            hostBuf[i], 1,
            "Post-reset increment incorrect at index " + std::to_string(i)
        );
    }

    tester.assertTrue(gpu->freeBuffer(newDevPtr), "freeBuffer() after reset failed");

    tester.debug("Emulator reset and reuse test complete");
    gpu->shutdown();
    return 0;
}
