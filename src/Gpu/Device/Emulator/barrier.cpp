/**
 * @file src/Gpu/Device/Emulator/barrier.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name barrier
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Synchronize all outstanding GPU operations (barrier).
     * @return true if barrier succeeded, false otherwise.
     */
    bool Emulator::barrier() {
        return true; // No-op for software simulator
    }

}
