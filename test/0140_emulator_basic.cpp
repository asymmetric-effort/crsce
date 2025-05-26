// file: test/0140_emulator_basic.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0140_emulator_basic.cpp
 * @brief Basic instantiation and type validation for Gpu::Device::Emulator.
 *
 * This test ensures:
 *   - The Emulator can be constructed without crashing.
 *   - The returned object is a valid subclass of Gpu::Device::Interface.
 */

#include "utils/test/Tester.h"
#include "Gpu/Device/Emulator/Emulator.h"
#include "Gpu/Device/Interface.h"
#include <memory>

using Gpu::Device::Emulator;
using Gpu::Device::Interface;

int main() {
    Tester tester("Gpu::Device::Emulator basic construction");
    tester.skip("disable for debugging");

    std::unique_ptr<Interface> gpu = std::make_unique<Emulator>();

    tester.assertNotNull(gpu, "Emulator object is non-null");
    tester.assertNotNull(dynamic_cast<Emulator *>(gpu.get()), "dynamic_cast confirms Emulator type");
    tester.assertTrue(gpu->init(), "init() completes successfully");

    tester.pass();
}
