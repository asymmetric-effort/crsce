/**
 * @file include/Gpu/Device/Cuda/Cuda.h
 * @brief Declare the interface for an nVidia CUDA GPU
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include "Gpu/Device/Interface.h"

namespace Gpu::Device {

    /**
     * @name Gpu::Device::Cuda
     * @brief Placeholder implementation of the GPU interface using CUDA backend.
     * @ref docs/Gpu/Design/Gpu-Cuda.md
     *
     * This is a stub and will not be implemented until later phases of the project.
     */
    class Cuda final : public Interface {
    public:
        Cuda() = default;
        ~Cuda() override = default;

        bool init() override { return false; }
        void shutdown() override {}
        void reset() override {}

        Common::AbstractPtr alloc(std::size_t) override { return 0; }
        bool free(Common::AbstractPtr&) override { return false; }
        bool write(const Common::Buffer8&, Common::AbstractPtr&) override { return false; }
        bool write(const Common::Buffer64&, Common::AbstractPtr&) override { return false; }
        bool read(Common::Buffer8&, Common::AbstractPtr&) override { return false; }
        bool read(Common::Buffer64&, Common::AbstractPtr&) override { return false; }

        bool registerKernel(KernelId, const Common::Buffer8&) override { return false; }
        bool launchTask(KernelId, const Common::Buffer8&) override { return false; }

        bool dot(Math::Matrix&, const Math::Matrix&, const Math::Matrix&) override { return false; }
        bool add(Math::Matrix&, const Math::Matrix&, const Math::Matrix&) override { return false; }
        bool sub(Math::Matrix&, const Math::Matrix&, const Math::Matrix&) override { return false; }
        bool mul(Math::Matrix&, const Math::Matrix&, const Math::Matrix&) override { return false; }
        bool transpose(Math::Matrix&, const Math::Matrix&) override { return false; }
        bool reduce(Math::Matrix&, const Math::Matrix&, bool) override { return false; }

        bool barrier() override { return false; }
        bool memfence() override { return false; }
        bool yield() override { return false; }
        bool wait(unsigned) override { return false; }
    };

} // namespace Gpu::Device
