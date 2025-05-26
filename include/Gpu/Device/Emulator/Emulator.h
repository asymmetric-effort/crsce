/**
 * @file include/Gpu/Device/Emulator/Emulator.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <memory>
#include <sys/types.h>
#include "Gpu/Ipc/Result.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Device/Interface.h"
#include "Gpu/Ipc/Communications.h"

namespace Gpu::Device {

    /**
     * @name Gpu::Device::Emulator
     * @brief Parent-side implementation of a mock GPU using forked IPC and software thread emulation.
     * @ref docs/Gpu/Design/Gpu-Emulator.md
     */
    class Emulator final : public Interface {
    public:
        Emulator();
        ~Emulator() override;

        bool init() override;
        void shutdown() override;
        void reset() override;

        Common::AbstractPtr alloc(std::size_t bytes) override;
        bool free(Common::AbstractPtr& ptr) override;
        bool write(const Common::Buffer8& source, Common::AbstractPtr& dst) override;
        bool write(const Common::Buffer64& source, Common::AbstractPtr& dst) override;
        bool read(Common::Buffer8& source, Common::AbstractPtr& dst) override;
        bool read(Common::Buffer64& source, Common::AbstractPtr& dst) override;

        bool registerKernel(KernelId id, const Common::Buffer8& binary) override;
        bool launchTask(KernelId id, const Common::Buffer8& args) override;

        bool dot(Math::Matrix& result, const Math::Matrix& lhs, const Math::Matrix& rhs) override;
        bool add(Math::Matrix& result, const Math::Matrix& lhs, const Math::Matrix& rhs) override;
        bool sub(Math::Matrix& result, const Math::Matrix& lhs, const Math::Matrix& rhs) override;
        bool mul(Math::Matrix& result, const Math::Matrix& lhs, const Math::Matrix& rhs) override;
        bool transpose(Math::Matrix& result, const Math::Matrix& mat) override;
        bool reduce(Math::Matrix& result, const Math::Matrix& mat, bool rowwise) override;

        bool barrier() override;
        bool memfence() override;
        bool yield() override;
        bool wait(unsigned deadline) override;

    private:
        pid_t childPid_ = 0;
        std::unique_ptr<Ipc::Communications> ipc_;
        bool initialized_ = false;
        bool shutdown_ = false;
    };

} // namespace Gpu::Device
