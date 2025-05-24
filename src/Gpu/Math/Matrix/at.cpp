// file: src/Gpu/Math/Matrix/at.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <format>
#include "Gpu/Math/Matrix.h"
#include "Gpu/Exceptions/MatrixOutOfRange.h"

namespace Gpu::Math {
    const double &Matrix::at(const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= cols_)
            throw Gpu::Exceptions::MatrixOutOfRange(
                std::format("index ({},{}) out of bounds ({},{})", r, c, rows_, cols_)
            );
        return buffer_[r * cols_ + c];
    }

    double &Matrix::at(const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= cols_)
            throw Gpu::Exceptions::MatrixOutOfRange(
                std::format("index ({},{}) out of bounds ({},{})", r, c, rows_, cols_)
            );
        return buffer_[r * cols_ + c];
    }
}
