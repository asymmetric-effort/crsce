// file: include/Gpu/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstddef>
#include <memory>
#include <iostream>

namespace Gpu {
    /**
     * This class is the interface for graphics processor abstraction.
     */
    class Interface {
    public:
        virtual ~Interface() = default;

        // Initialize the GPU device or emulator
        virtual bool init() = 0;

        // Allocate `bytes` of memory on the GPU (or emulator)
        virtual void* allocBuffer(std::size_t bytes) = 0;

        // Free GPU memory previously allocated
        virtual bool freeBuffer(void* ptr) = 0;

        // Copy `bytes` from host `src` into GPU memory (`dst`)
        virtual bool writeBuffer(void* dst, const void* src, std::size_t bytes) = 0;

        // Copy `bytes` from GPU memory (`src`) back into host memory (`dst`)
        virtual bool readBuffer(void* dst, const void* src, std::size_t bytes) = 0;

        // Launch an asynchronous task (kernel) on the GPU or emulator
        // The provided function will be invoked concurrently
        virtual bool launchTask(const std::function<void()>& task) = 0;

        // Block until all outstanding tasks have completed
        virtual bool sync() = 0;

        // Factory: create concrete implementation based on compile-time flags
        static std::unique_ptr<Interface> create();
    };
} // namespace Gpu
