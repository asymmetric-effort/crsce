// file: src/Gpu/Device/Emulator.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once
#include "Gpu/Interface.h"
#include <iostream>

namespace Gpu {

    class Emulator : public Interface {
    public:
        Emulator();
        virtual ~Emulator();

        bool init() override;
        // Additional emulator-specific methods
    };

} // namespace Gpu

