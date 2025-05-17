// file: include/Gpu/Interface.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once
#include <memory>

namespace Gpu {

    class Interface {
    public:

        virtual ~Interface() = default;

        // Initialize the GPU device or emulator
        virtual bool init() = 0;

        // Other abstract GPU operations (enqueue kernels, transfer memory, etc.)

        // Factory: create concrete implementation based on compile-time flags
        static std::unique_ptr<Interface> create();
    };

} // namespace Gpu

