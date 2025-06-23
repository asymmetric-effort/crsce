/**
 * @file include/Gpu/Ipc/CommandType.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <cstdint>

namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::CommandType
     * @brief Represents the type of IPC command issued from the parent to the mock GPU.
     * @enum Gpu::Ipc::CommandType
     * @ref docs/Gpu/Design/Gpu-Ipc-CommandType.md
     *
     * These values define the operational intent of a message sent to the child GPU process. Each
     * type maps to a corresponding handler in Gpu::RuntimeManager and triggers a defined effect.
     *
     * @example
     * Gpu::Ipc::CommandType cmd = Gpu::Ipc::CommandType::Alloc;
     * if (cmd == Gpu::Ipc::CommandType::Shutdown) {
     *    -- Trigger graceful shutdown --
     * }
     */
    enum class CommandType : uint32_t {
        Init = 0x00, ///< Initialize the emulator (no-op in most cases)
        Alloc = 0x01, ///< Allocate device memory
        Free = 0x02, ///< Free previously allocated memory
        Write = 0x03, ///< Write data to a device memory region
        Read = 0x04, ///< Read data from a device memory region
        RegisterKernel = 0x05, ///< Register a binary kernel blob
        LaunchTask = 0x06, ///< Launch a kernel thread by ID
        Reset = 0x07, ///< Reset all emulator state except process lifetime
        Shutdown = 0x08 ///< Fully terminate emulator state and exit child process
    };
}
