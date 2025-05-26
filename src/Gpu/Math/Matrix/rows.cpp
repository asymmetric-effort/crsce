/**
 * @file src/Gpu/Math/Matrix/rows.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Math/Matrix.h"

namespace Gpu::Math {

    std::size_t Matrix::rows() const noexcept {
        return rows_;
    }

}
