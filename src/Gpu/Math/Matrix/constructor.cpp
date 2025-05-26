/**
 * @file src/Gpu/Math/Matrix/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Math/Matrix.h"

namespace Gpu::Math {
    Matrix::Matrix(const std::size_t rows, const std::size_t cols)
        : rows_(rows),
          cols_(cols),
          buffer_(rows * cols, 0) {
    }
}
