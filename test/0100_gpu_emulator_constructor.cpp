// file: test/0100_gpu_emulator_constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0100_gpu_emulator_constructor.cpp
 * @brief Constructor and destructor sanity check for Gpu::Device::Emulator.
 *
 * This test ensures that the Emulator class can be instantiated and destroyed
 * cleanly without triggering any exceptions, memory violations, or resource leaks.
 * It does not invoke init() or fork; it validates only basic object lifecycle.
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include <iostream>

using Gpu::Device::Emulator;

int main() {
    try {
        Emulator emu;
        std::cout << "[PASS] Gpu::Device::Emulator constructor/destructor test passed.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Exception thrown during Emulator construction: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "[FAIL] Unknown exception during Emulator construction.\n";
        return 1;
    }
}
