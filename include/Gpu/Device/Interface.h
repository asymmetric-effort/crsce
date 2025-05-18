// file: include/Gpu/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/common/KernelId.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>


namespace Gpu {

    class Interface {
    public:
        virtual ~Interface() = default;

        // Initialize the GPU device or emulator
        virtual bool init() = 0;

        // Memory management
        virtual void* allocBuffer(std::size_t bytes) = 0;
        virtual bool freeBuffer(void* ptr) = 0;

        // Data transfer
        virtual bool writeBuffer(void* dst, const void* src, std::size_t bytes) = 0;
        virtual bool readBuffer(void* dst, const void* src, std::size_t bytes) = 0;

        virtual bool launchKernel(KernelId id, void* buffer, std::size_t count) =0;

        // Task dispatch
        virtual bool sync() = 0;

        // Factory
        static std::unique_ptr<Interface> create();
    };

} // namespace Gpu
