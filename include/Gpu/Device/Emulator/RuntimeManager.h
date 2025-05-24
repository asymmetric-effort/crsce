// file: include/Gpu/RuntimeManager.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/MemoryTracker.h"
#include "ThreadRegistry.h"
#include "Gpu/Common/KernelManager.h"

namespace Gpu::Device {
    /**
     * @name Gpu::RuntimeManager
     * @brief Handles all kernel/memory/IPC operations dispatched from MockGpu.
     * @ref docs/Gpu/Design/Gpu-RuntimeManager.md
     */
    class RuntimeManager {
    public:
        RuntimeManager() = default;

        ~RuntimeManager() = default;

        Gpu::Ipc::Response handleAlloc(const Gpu::Ipc::Message &);

        Gpu::Ipc::Response handleFree(const Gpu::Ipc::Message &);

        Gpu::Ipc::Response handleWrite(const Gpu::Ipc::Message &, const Common::Buffer8 &payload);

        Gpu::Ipc::Response handleRead(const Gpu::Ipc::Message &) const;

        Gpu::Ipc::Response handleRegisterKernel(const Gpu::Ipc::Message &, const Common::Buffer8 &blob);

        Gpu::Ipc::Response handleLaunchTask(const Gpu::Ipc::Message &, const Common::Buffer8 &args);

        Gpu::Ipc::Response handleReset();

        Gpu::Ipc::Response handleShutdown();

        bool isShutdown() const;

    private:
        Gpu::Ipc::MemoryTracker memory_;
        Gpu::Device::ThreadRegistry threads_;
        Gpu::KernelManager kernels_;
        bool shutdown_ = false;
    };
} // namespace Gpu
