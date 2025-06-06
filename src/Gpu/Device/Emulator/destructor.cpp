/**
 * @file src/Gpu/Device/Emulator/destructor.cpp
 * @brief Define a GPU Emulator Device Class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"
#include <sys/wait.h>
#include <unistd.h>
/**
 * @namespace Gpu::Device
 */
namespace Gpu::Device {

    /**
     * @name destructor
     * @public
     * @brief Destructor ensures proper shutdown.
     */
    Emulator::~Emulator() {
        shutdown();
    }

}
