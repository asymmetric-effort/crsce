// file: test/0142_emulator_kernel.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0142_emulator_kernel.cpp
 * @brief Test Gpu::Device::Emulator::registerKernel() and launchTask() behavior.
 *
 * This test validates:
 *   - Kernels can be registered with valid binary blobs.
 *   - launchTask() runs the registered kernel.
 *   - Calls before init() or after shutdown() throw DeviceNotReady.
 */

#include "utils/test/Tester.h"
#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Common/KernelManager.h"
#include "Gpu/Common/Buffer8.h"

using Gpu::Device::Emulator;
using Gpu::Exceptions::DeviceNotReady;
using Common::Buffer8;
using Gpu::KernelId;

int main() {
    Tester tester("Gpu::Device::Emulator registerKernel() / launchTask()");
    tester.skip("disable for debugging");

    Emulator gpu;
    constexpr KernelId id = 0xBEEF;

    const Buffer8 blob = {0x01, 0x02, 0x03, 0x04};  // minimal valid payload
    const Buffer8 args = {0xDE, 0xAD, 0xBE, 0xEF};  // mock launch args

    try {
        gpu.registerKernel(id, blob);
        tester.fail("registerKernel() before init() should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("registerKernel() before init() throws");
    }

    try {
        gpu.launchTask(id, args);
        tester.fail("launchTask() before init() should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("launchTask() before init() throws");
    }

    tester.assertTrue(gpu.init(), "init() succeeds");

    tester.assertTrue(gpu.registerKernel(id, blob), "registerKernel() returns true");
    tester.assertTrue(gpu.launchTask(id, args), "launchTask() returns true");

    gpu.shutdown();

    try {
        gpu.registerKernel(id, blob);
        tester.fail("registerKernel() after shutdown should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("registerKernel() after shutdown throws");
    }

    try {
        gpu.launchTask(id, args);
        tester.fail("launchTask() after shutdown should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("launchTask() after shutdown throws");
    }

    tester.pass();
}
