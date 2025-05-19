// file: test/0200_Gpu_Emulator_HelloWorld.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Device/Interface.h"
#include "utils/test/Tester.h"
#include <cstring>

int main() {
    Tester tester("test/0200_Gpu_HelloWorld", TerminateOnError);
    tester.deadline(/*default 60s*/);

    // Create and initialize GPU (emulator)
    auto gpu = Gpu::Interface::create();
    tester.assertNotNull(gpu, "Failed to create GPU emulator instance");

    bool initOk = gpu->init();
    tester.assertTrue(initOk, "GPU emulator init() failed");
    tester.debug("[0200] init() succeeded. Emulator child running.");

    // Message to round-trip
    const char* msg = "Hello, GPU!";
    size_t len = std::strlen(msg) + 1;

    // Allocate GPU buffer
    void* devPtr = gpu->allocBuffer(len);
    tester.assertNotNull(devPtr, "allocBuffer() returned nullptr");

    // Write message to GPU memory
    bool writeOk = gpu->writeBuffer(devPtr, msg, len);
    tester.assertTrue(writeOk, "writeBuffer() failed");

    // Read back into host buffer
    char* readBuf = new char[len];
    bool readOk = gpu->readBuffer(readBuf, devPtr, len);
    tester.assertTrue(readOk, "readBuffer() failed");

    // Verify content
    tester.assertTrue(std::string(readBuf) == msg, "Round-trip string mismatch");
    tester.debug(std::format("[0200] Round-trip succeeded: 0x{:X}", static_cast<int>(readBuf[0])));

    delete[] readBuf;

    // Free GPU buffer
    bool freeOk = gpu->freeBuffer(devPtr);
    tester.assertTrue(freeOk, "freeBuffer() failed");

    // Shutdown and wait
    bool waitOk = gpu->wait();
    tester.assertTrue(waitOk, "wait() failed");
    tester.debug("[0200] wait() succeeded. Emulator child terminated.");

    return 0;
}
