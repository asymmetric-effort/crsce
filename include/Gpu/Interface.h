// file: include/Gpu/Interface.h
#pragma once

#include <memory>

namespace Gpu {

    class Interface {
    public:

        // constructor
        virtual Interface() = default;

        // destructor
        virtual ~Interface() = default;

        // Initialize the GPU device or emulator
        virtual bool init() = 0;

        // Other abstract GPU operations (enqueue kernels, transfer memory, etc.)

        // Factory: create concrete implementation based on compile-time flags
        static std::unique_ptr<Interface> create();
    };

} // namespace Gpu
