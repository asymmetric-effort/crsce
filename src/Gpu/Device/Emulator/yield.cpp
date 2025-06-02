/**
 * @file src/Gpu/Device/Emulator/yield.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include <thread>

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name yield
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Yield execution of the current GPU task.
     * @return true if yield succeeded, false otherwise.
     */
    bool Emulator::yield() {
        std::this_thread::yield();
        return true;
    }

}
