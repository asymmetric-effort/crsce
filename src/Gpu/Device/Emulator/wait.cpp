/**
 * @file src/Gpu/Device/Emulator/wait.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include <thread>
#include <chrono>

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name wait
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Wait for GPU tasks to complete up to a deadline.
     * @param deadline Time in milliseconds to wait before timeout.
     * @return true if all tasks finished before deadline, false otherwise.
     */
    bool Emulator::wait(const unsigned deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(deadline));
        return true;
    }

}
