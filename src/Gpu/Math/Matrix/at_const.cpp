// file: src/Gpu/Math/Matrix/at_const.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"
#include <stdexcept>

namespace Gpu::Math {

    const uint64_t& Matrix::at(const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= cols_)
            throw std::out_of_range("Matrix::at() const: index out of bounds");
        return buffer_[r * cols_ + c];
    }

}
