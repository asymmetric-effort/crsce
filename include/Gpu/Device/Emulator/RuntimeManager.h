// file: include/Gpu/RuntimeManager.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file include/Gpu/RuntimeManager.h
 * @brief Declare the RuntimeManager class which runs inside the MockGpu to manage kernel runtimes and memory.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/MemoryTracker.h"
#include "ThreadRegistry.h"
#include "Common/KernelManager.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @class RuntimeManager
     * @brief Handles all kernel, memory, and IPC operations dispatched from the MockGpu.
     *
     * The RuntimeManager processes IPC messages for allocation, deallocation, data transfer,
     * kernel registration, and task launching. It maintains memory tracking, thread registry,
     * and kernel metadata to emulate GPU runtime behavior.
     * @ref docs/Gpu/Design/Gpu-RuntimeManager.md
     */
    class RuntimeManager {
    public:
        /**
         * @name constructor
         * @public
         * @brief Default constructor.
         */
        RuntimeManager() = default;

        /**
         * @name destructor
         * @public
         * @brief Default destructor.
         */
        ~RuntimeManager() = default;

        /**
         * @name handleAlloc
         * @public
         * @brief Handle an allocation request from IPC Message.
         * @param msg IPC message containing allocation parameters.
         * @return Response indicating success or failure and any metadata.
         */
        Gpu::Ipc::Response handleAlloc(const Gpu::Ipc::Message &msg);

        /**
         * @name handleFree
         * @public
         * @brief Handle a free request from IPC Message.
         * @param msg IPC message specifying which memory to free.
         * @return Response indicating success or failure of deallocation.
         */
        Gpu::Ipc::Response handleFree(const Gpu::Ipc::Message &msg);

        /**
         * @name handleWrite
         * @public
         * @brief Handle a write request with payload.
         * @param msg IPC message specifying destination address and size.
         * @param payload Buffer containing data to write.
         * @return Response indicating success or failure of write operation.
         */
        Gpu::Ipc::Response handleWrite(const Gpu::Ipc::Message &msg, const Common::Buffer8 &payload);

        /**
         * @name handleRead
         * @public
         * @brief Handle a read request from IPC.
         * @param msg IPC message specifying source address and size.
         * @return Response containing requested data or error code.
         */
        Gpu::Ipc::Response handleRead(const Gpu::Ipc::Message &msg) const;

        /**
         * @name handleRegisterKernel
         * @public
         * @brief Handle kernel registration request.
         * @param msg IPC message specifying kernel ID.
         * @param blob Binary blob containing compiled kernel code.
         * @return Response indicating success or failure of registration.
         */
        Gpu::Ipc::Response handleRegisterKernel(const Gpu::Ipc::Message &msg, const Common::Buffer8 &blob);

        /**
         * @name handleLaunchTask
         * @public
         * @brief Handle a kernel launch request.
         * @param msg IPC message specifying kernel ID and launch parameters.
         * @param args Argument buffer for the kernel.
         * @return Response indicating success or failure of launch.
         */
        Gpu::Ipc::Response handleLaunchTask(const Gpu::Ipc::Message &msg, const Common::Buffer8 &args);

        /**
         * @name handleReset
         * @public
         * @brief Handle a reset request, reinitializing internal state.
         * @return Response indicating reset completion status.
         */
        Gpu::Ipc::Response handleReset();

        /**
         * @name handleShutdown
         * @public
         * @brief Handle a shutdown request, marking runtime for termination.
         * @return Response indicating shutdown completion.
         */
        Gpu::Ipc::Response handleShutdown();

        /**
         * @name isShutdown
         * @public
         * @brief Query whether shutdown has been initiated.
         * @return true if shutdown has been requested, false otherwise.
         */
        bool isShutdown() const;

    private:
        /**
         * @property memory_
         * @private
         * @brief Tracks GPU memory allocations and deallocations.
         */
        Gpu::Ipc::MemoryTracker memory_;

        /**
         * @property threads_
         * @private
         * @brief Manages CPU threads simulating GPU compute units.
         */
        Gpu::Device::ThreadRegistry threads_;

        /**
         * @property kernels_
         * @private
         * @brief Manages registered kernel binaries and metadata.
         */
        Common::KernelManager kernels_;

        /**
         * @property shutdown_
         * @private
         * @brief Indicates whether shutdown has been requested.
         */
        bool shutdown_ = false;
    };
} // namespace Gpu::Device
