/**
 * @file include/Gpu/Ipc/Message/MessageType.h
 * @brief Declare types supporting the InterProcess Communication (IPC) mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <cstdint>
#include <format>

namespace Gpu::Ipc::Message {
    /**
     * @name Gpu::Ipc::Message::Type
     * @enum Gpu::Ipc::Message::Type
     * @brief Represents the type of IPC command issued from the parent to the mock GPU. These values
     *        define the operational intent of a message sent to the child GPU process. Each type maps
     *        to a corresponding handler in Gpu::RuntimeManager and triggers a defined effect.
     * @ref docs/Gpu/Design/Gpu-Ipc-MessageType.md
     */
    enum class Type : uint8_t {
        Noop = 0x0, /// < No operation.  Disregard.

        GpuInitialize = 0x01, ///< Initialize the Gpu (no-op in most cases)
        GpuInitializeResult = GpuInitialize + 1, ///< Result of GpuInitialize (error state)
        GpuReset = GpuInitializeResult + 1, ///< Reset the GPU state.
        GpuResetResult = GpuReset + 1, ///< GpuReset outcome (error state)
        MemoryAlloc = GpuResetResult + 1, ///< Allocate device memory
        MemoryAllocResult = MemoryAlloc + 1, ///< Memory was allocated (returns AbstractPtr)
        MemoryFree = MemoryAllocResult + 1, ///< Free previously allocated memory (secure delete)
        MemoryFreeResult = MemoryFree + 1, ///< Result of a MemoryFree (pass/fail)
        MemorySize = MemoryFreeResult + 1, ///< Get size of memory region
        MemorySizeResult = MemorySize + 1, ///< Result of MemorySize request (size of a given region)
        MemoryRead = MemorySizeResult + 1, ///< read a specific GPU memory region (AbstractPtr, Size)
        MemoryReadResult = MemoryRead + 1, ///< result of MemoryRead (byte buffer of contents)
        MemoryWrite = MemoryReadResult + 1, ///< Read a specific GPU memory region (AbstractPtr, byte buffer)
        MemoryWriteResult = MemoryWrite + 1, ///< result of MemoryWrite (error state)
        KernelRegister = MemoryWriteResult + 1, ///< Register a binary kernel blob (Blob)
        KernelRegisterResult = KernelRegister + 1, ///< Result of KernelRegister (KernelId)
        KernelFree = KernelRegisterResult + 1, ///< Free a registered kernel blob (KernelId)
        KernelFreeResult = KernelFree + 1, ///< Result of KernelFree (error state)
        KernelList = KernelFreeResult + 1, ///< List currently registered kernels (Id and hash)
        KernelListResult = KernelList + 1, ///< Result of KernelList (list of kernels)
        TaskLaunch = KernelListResult + 1, ///< Launch the GPU task described by a given kernelId
        TaskLaunchResult = TaskLaunch + 1, ///< Result of TaskLaunch (returns TaskId, error state)
        TaskStop = TaskLaunchResult + 1, ///< Stop a running GPU task (identified by taskId)
        TaskStopResult = TaskStop + 1, ///< Result of TaskStop (error state)
        ReqShutdown = TaskStopResult + 1, ///< Terminate the GPU Controller
        // Add more values here if needed...
        MessageTypeMax = ReqShutdown ///< The maximum value when deserializing
    };

    /**
     * @name message_type_to_string
     * @brief return the string representing the MessageType
     * @param expected_type
     * @return std::string
     */
    inline std::string message_type_to_string(Type& expected_type) {
        switch (expected_type) {
        case Type::Noop: return "Noop";
        case Type::GpuInitialize: return "GpuInitialize";
        case Type::GpuInitializeResult: return "GpuInitializeResult";
        case Type::GpuReset: return "GpuReset";
        case Type::GpuResetResult: return "GpuResetResult";
        case Type::MemoryAlloc: return "MemoryAlloc";
        case Type::MemoryAllocResult: return "MemoryAllocResult";
        case Type::MemoryFree: return "MemoryFree";
        case Type::MemoryFreeResult: return "MemoryFreeResult";
        case Type::MemorySize: return "MemorySize";
        case Type::MemorySizeResult: return "MemorySizeResult";
        case Type::MemoryRead: return "MemoryRead";
        case Type::MemoryReadResult: return "MemoryReadResult";
        case Type::MemoryWrite: return "MemoryWrite";
        case Type::MemoryWriteResult: return "MemoryWriteResult";
        case Type::KernelRegister: return "KernelRegister";
        case Type::KernelRegisterResult: return "KernelRegisterResult";
        case Type::KernelList: return "KernelList";
        case Type::TaskLaunch: return "TaskLaunch";
        case Type::TaskLaunchResult: return "TaskLaunchResult";
        case Type::TaskStop: return "TaskStop";
        case Type::TaskStopResult: return "TaskStopResult";
        case Type::ReqShutdown: return "ReqShutdown";
        default:
            throw std::runtime_error(std::format("undefined method {}", static_cast<uint8_t>(expected_type)));
        }
    }

    /**
     * @name verify_message_type
     * @brief used in deserialize operations, this performs common checks for MessageType
     * @param buffer
     * @param expected_type
     */
    inline void verify_message_type(const Common::Buffer8& buffer, Type& expected_type) {
        if (buffer.empty())
            throw std::runtime_error("Gpu::Ipc::deserialize: buffer too small for MessageType");
        const auto message_type = static_cast<Type>(static_cast<uint8_t>(buffer[0]));
        if (message_type > Type::MessageTypeMax)
            throw std::out_of_range("Gpu::Ipc::deserialize: value out of range");
        if (message_type != expected_type)
            throw std::runtime_error(std::format("expected {}", message_type_to_string(expected_type)));
    }
}
