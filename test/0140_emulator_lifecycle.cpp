// file: test/0140_emulator_lifecycle.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0140_emulator_lifecycle.cpp
 * @brief Unit test for Gpu::Device::Emulator lifecycle methods: init(), shutdown(), reset().
 *
 * This test ensures:
 *   - init() succeeds once and is idempotent before shutdown.
 *   - reset() is valid only after init() and before shutdown.
 *   - shutdown() succeeds once and becomes final.
 *   - post-shutdown calls throw Gpu::Exceptions::DeviceNotReady.
 */

#include "utils/test/Tester.h"
#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"

#include <memory>

using Gpu::Device::Emulator;
using Gpu::Exceptions::DeviceNotReady;

int main() {
    Tester tester("Gpu::Device::Emulator lifecycle");

    Emulator gpu;

    tester.assertTrue(gpu.init(), "Initial init() succeeds");
    tester.assertTrue(gpu.init(), "Second init() is idempotent");

    gpu.reset();
    tester.assertTrue(gpu.init(), "init() after reset is allowed");

    gpu.shutdown();
    tester.pass("shutdown() succeeds");

    try {
        gpu.init();
        tester.fail("init() after shutdown should throw");
    } catch (const DeviceNotReady&) {
        tester.pass("Caught DeviceNotReady after shutdown/init()");
    }

    try {
        gpu.reset();
        tester.fail("reset() after shutdown should throw");
    } catch (const DeviceNotReady&) {
        tester.pass("Caught DeviceNotReady after shutdown/reset()");
    }

    try {
        gpu.shutdown();
        tester.pass("shutdown() is idempotent after shutdown");
    } catch (...) {
        tester.fail("shutdown() after shutdown must not throw");
    }

    tester.pass();
}
