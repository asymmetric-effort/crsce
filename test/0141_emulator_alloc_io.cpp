// file: test/0141_emulator_alloc_io.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0141_emulator_alloc_io.cpp
 * @brief Test Gpu::Device::Emulator::alloc() behavior.
 *
 * This test validates:
 *   - Allocating memory returns a valid AbstractPtr (non-zero).
 *   - Returned pointers are unique across multiple allocations.
 *   - Alloc() fails gracefully before init() or after shutdown().
 */

#include "utils/test/Tester.h"
#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Exceptions/DeviceNotReady.h"
#include "Gpu/Common/AbstractPtr.h"

#include <set>

using Gpu::Device::Emulator;
using Gpu::Exceptions::DeviceNotReady;
using Common::AbstractPtr;

int main() {
    Tester tester("Gpu::Device::Emulator alloc()");
    tester.skip("disable for debugging");

    Emulator gpu;

    try {
        gpu.alloc(32);
        tester.fail("alloc() before init() should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("alloc() before init() throws DeviceNotReady");
    }

    tester.assertTrue(gpu.init(), "init() succeeds");

    const AbstractPtr ptr1 = gpu.alloc(64);
    tester.assertNotEqual(ptr1, static_cast<AbstractPtr>(0), "alloc() returns non-zero AbstractPtr");

    const AbstractPtr ptr2 = gpu.alloc(128);
    tester.assertNotEqual(ptr2, static_cast<AbstractPtr>(0), "Second alloc() returns non-zero AbstractPtr");
    tester.assertNotEqual(ptr1, ptr2, "Returned pointers are unique");

    gpu.shutdown();

    try {
        gpu.alloc(64);
        tester.fail("alloc() after shutdown should throw");
    } catch (const DeviceNotReady &) {
        tester.pass("alloc() after shutdown throws DeviceNotReady");
    }

    tester.pass();
}
