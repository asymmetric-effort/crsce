/**
 * @file src/Gpu/Device/Emulator/read_Buffer64.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu::Device {

    bool Emulator::read(Common::Buffer64& source, Common::AbstractPtr& dst) {
        Common::Buffer8 temp(source.size() * sizeof(uint64_t));
        if (!read(temp, dst)) return false;

        const uint64_t* src = reinterpret_cast<const uint64_t*>(temp.data());
        source.assign(src, src + source.size());
        return true;
    }

}
