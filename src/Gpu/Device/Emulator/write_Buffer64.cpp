/**
 * @file src/Gpu/Device/Emulator/write_Buffer64.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name write
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Write a 64-bit buffer to GPU memory.
     * @param source Data buffer to write.
     * @param dst Abstract pointer to destination GPU memory.
     * @return true if write succeeded, false otherwise.
     */
    bool Emulator::write(const Common::Buffer64& source, Common::AbstractPtr& dst) {
        const auto data = reinterpret_cast<const uint8_t*>(source.data());
        const Common::Buffer8 temp(data, data + (source.size() * sizeof(uint64_t)));
        return write(temp, dst);
    }

}
