/**
 * @file src/Gpu/Device/Emulator/memfence.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name memfence
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Perform a memory fence on the GPU emulator.
     * @return true if memfence succeeded, false otherwise.
     */
    bool Emulator::memfence() {
        return true; // No memory reordering at emulation level
    }

}
