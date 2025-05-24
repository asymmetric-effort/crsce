// file: src/Gpu/Math/Matrix/at.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"
#include "Gpu/Exceptions/MatrixOutOfRange.h"

namespace Gpu::Math {

    const double& Matrix::at(const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= cols_)
            throw Gpu::Exceptions::MatrixOutOfRange("index out of bounds");
        return buffer_[r * cols_ + c];
    }

}
