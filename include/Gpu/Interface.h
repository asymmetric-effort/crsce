// file: include/Gpu/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstddef>
#include <memory>
#include <iostream>

namespace Gpu {

    class Interface {
    public:
        virtual ~Interface() = default;

        // Initialize the GPU device or emulator
        virtual bool init() = 0;

        // Allocate `bytes` of memory on the GPU (or emulator)
        virtual void* allocBuffer(std::size_t bytes) = 0;

        // Free GPU memory previously allocated
        virtual bool freeBuffer(void* ptr) = 0;

        // Copy `bytes` from host `src` into GPU memory at `dst`
        virtual bool writeBuffer(void* dst, const void* src, std::size_t bytes) = 0;

        // Copy `bytes` from GPU memory at `src` back to host `dst`
        virtual bool readBuffer(void* dst, const void* src, std::size_t bytes) = 0;

        // Factory: create concrete implementation based on compile-time flags
        static std::unique_ptr<Interface> create();
    };

} // namespace Gpu
