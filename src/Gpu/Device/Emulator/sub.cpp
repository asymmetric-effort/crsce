/**
 * @file src/Gpu/Device/Emulator/sub.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Device/Emulator/Emulator.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Device {

    /**
     * @name sub
     * @class Emulator
     * @memberof Interface
     * @public
     * @brief Perform element-wise subtraction of two matrices.
     * @param result Output matrix to store difference.
     * @param lhs Left-hand side matrix.
     * @param rhs Right-hand side matrix.
     * @return true if subtraction succeeded, false otherwise.
     */
    bool Emulator::sub(Math::Matrix& result, const Math::Matrix& lhs, const Math::Matrix& rhs) {
        return false; // Unimplemented
    }

}
