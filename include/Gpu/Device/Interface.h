// file: include/Gpu/Device/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <cstddef>
#include "Gpu/Common/AbstractPtr.h"
#include "Gpu/Common/Buffer8.h"
#include "Gpu/Common/Buffer64.h"

namespace Gpu::Math { class Matrix; }

namespace Gpu::Device {

    /**
     * @name Gpu::Device::Interface
     * @brief Abstract interface defining all operations supported by any GPU backend.
     * @ref docs/Gpu/Design/Gpu-Interface.md
     */
    class Interface {
    public:
        virtual ~Interface() = default;

        // Lifecycle
        virtual bool init() = 0;
        virtual void shutdown() = 0;
        virtual void reset() = 0;

        // Memory
        virtual Common::AbstractPtr alloc(std::size_t bytes) = 0;
        virtual bool free(Common::AbstractPtr& ptr) = 0;
        virtual bool write(const Common::Buffer8& source, Common::AbstractPtr& dst) = 0;
        virtual bool write(const Common::Buffer64& source, Common::AbstractPtr& dst) = 0;
        virtual bool read(Common::Buffer8& source, Common::AbstractPtr& dst) = 0;
        virtual bool read(Common::Buffer64& source, Common::AbstractPtr& dst) = 0;

        // Kernel control
        using KernelId = uint64_t;
        virtual bool registerKernel(KernelId id, const Common::Buffer8& binary) = 0;
        virtual bool launchTask(KernelId id, const Common::Buffer8& args = {}) = 0;

        // Matrix math
        virtual bool dot(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs) = 0;
        virtual bool add(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs) = 0;
        virtual bool sub(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs) = 0;
        virtual bool mul(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& lhs, const Gpu::Math::Matrix& rhs) = 0;
        virtual bool transpose(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat) = 0;
        virtual bool reduce(Gpu::Math::Matrix& result, const Gpu::Math::Matrix& mat, bool rowwise) = 0;

        // Synchronization
        virtual bool barrier() = 0;
        virtual bool memfence() = 0;
        virtual bool yield() = 0;
        virtual bool wait(unsigned deadline) = 0;
    };

} // namespace Gpu::Device
