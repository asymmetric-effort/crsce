// file: src/Gpu/Math/Matrix/at_mutable.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"
#include <stdexcept>

namespace Gpu::Math {

    uint64_t& Matrix::at(std::size_t r, std::size_t c) {
        if (r >= rows_ || c >= cols_)
            throw std::out_of_range("Matrix::at() non-const: index out of bounds");
        return buffer_[r * cols_ + c];
    }

}
