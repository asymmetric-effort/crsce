// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu.h"

namespace Gpu {

    class Emulator : public Interface {

    public:

        Emulator();

        virtual ~Emulator();

        bool init() override;

        // Additional emulator-specific methods

    };

} // namespace Gpu
