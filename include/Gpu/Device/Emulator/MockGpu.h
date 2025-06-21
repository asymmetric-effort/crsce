/**
 * @file include/Gpu/Device/Emulator/MockGpu.h
 * @brief Declare the class representing a child class which emulates the behavior of a GPU for development and
 *        testing.  This class is used by the Gpu::Device::Emulator class.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Gpu/Ipc/Communications.h"
#include "RuntimeManager.h"

namespace Gpu::Device {

    /**
     * @name Gpu::Device::MockGpu
     * @brief Child-side command processor for emulated GPU runtime.
     * @ref docs/Gpu/Design/Gpu-Device-MockGpu.md
     *
     * Runs a blocking message loop that receives IPC messages and dispatches them
     * using Gpu::RuntimeManager. This is the child process peer to Emulator.
     */
    class MockGpu final {
    public:
        explicit MockGpu(Ipc::Communications& comm);
        void run();

    private:
        Ipc::Communications& ipc_;
        RuntimeManager runtime_{};
    };

} // namespace Gpu::Device
