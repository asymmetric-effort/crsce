// file: include/Gpu/Device/Emulator.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Interface.h"
#include <cstddef>
#include <iostream>

namespace Gpu {

    class Emulator : public Interface {
    public:

        Emulator();

        virtual ~Emulator();

        bool init() override;

        void* allocBuffer(std::size_t bytes) override;

        bool freeBuffer(void* ptr) override;

        bool writeBuffer(void* dst, const void* src, std::size_t bytes) override;

        bool readBuffer(void* dst, const void* src, std::size_t bytes) override;

    };

} // namespace Gpu
