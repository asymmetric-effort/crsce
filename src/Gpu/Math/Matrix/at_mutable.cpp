// file: src/Gpu/Math/Matrix/at_mutable.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"
#include <stdexcept>

namespace Gpu::Math {

    double& Matrix::at(const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= cols_)
            throw Gpu::Exceptions::MatrixOutOfRange("Matrix::at() non-const: index out of bounds");
        return buffer_[r * cols_ + c];
    }

}
