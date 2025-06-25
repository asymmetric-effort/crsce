/**
 * @file include/Gpu/Ipc/CommandType.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <cstdint>

namespace Gpu::Ipc {
    /**
     * @name Gpu::Ipc::MessageType
     * @brief Represents the type of IPC command issued from the parent to the mock GPU.
     * @enum Gpu::Ipc::MessageType
     * @ref docs/Gpu/Design/Gpu-Ipc-MessageType.md
     *
     * These values define the operational intent of a message sent to the child GPU process. Each
     * type maps to a corresponding handler in Gpu::RuntimeManager and triggers a defined effect.
     */
    enum class MessageType : uint32_t {
        Noop = 0x0, /// < No operation.  Disregard.

        InitializeGpu = 0x01, ///< Initialize the Gpu (no-op in most cases)
        ResetGpu = 0x02, ///< Reset the GPU state.

        MemoryAlloc = 0x10, ///< Allocate device memory
        MemoryFree = 0x11, ///< Free previously allocated memory (secure delete)
        MemorySize = 0x12, ///< Get size of memory region

        MemoryRead = 0x1E, ///< read a specific GPU memory region
        MemoryWrite = 0x1F, ///< Read a specific GPU memory region

        KernelRegister = 0x20, ///< Register a binary kernel blob
        KernelFree = 0x21, ///< Free a registered kernel blob
        KernelList = 0x22, ///< List currently registered kernels (Id and hash)

        TaskLaunch = 0x30, ///< Launch the GPU task described by a given kernel
        TaskStop = 0x31, ///< Stop a running GPU task (identified by taskId)

        ReqShutdown = 0xFF ///< Terminate the GPU Controller
    };
}
