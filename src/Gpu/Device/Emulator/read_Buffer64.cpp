/**
 * @file src/Gpu/Device/Emulator/read_Buffer64.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {
    /**
     * @name read
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Read data from GPU memory into a 64-bit buffer.
     * @param source Abstract pointer to GPU memory source.
     * @param dst Data buffer to be populated with read values.
     * @return true if read succeeded, false otherwise.
     */
    bool Emulator::read(Common::Buffer64& source, Common::AbstractPtr& dst) {
        Common::Buffer8 temp(source.size() * sizeof(uint64_t));
        if (!read(temp, dst)) return false;

        const uint64_t* src = reinterpret_cast<const uint64_t*>(temp.data());
        source.assign(src, src + source.size());
        return true;
    }

}
