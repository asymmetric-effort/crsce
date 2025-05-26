/**
 * @file src/Gpu/Math/Matrix/cols.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Math/Matrix.h"

namespace Gpu::Math {

    std::size_t Matrix::cols() const noexcept {
        return cols_;
    }

}
