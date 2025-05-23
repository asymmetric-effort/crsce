// file: src/Gpu/Math/Matrix/at.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"
#include <stdexcept>

namespace Gpu::Math {

    const uint64_t& Matrix::at(std::size_t r, std::size_t c) const {
        if (r >= rows_ || c >= cols_)
            throw std::out_of_range("Gpu::Math::Matrix::at(): index out of bounds");
        return buffer_[r * cols_ + c];
    }

    uint64_t& Matrix::at(std::size_t r, std::size_t c) {
        if (r >= rows_ || c >= cols_)
            throw std::out_of_range("Gpu::Math::Matrix::at(): index out of bounds");
        return buffer_[r * cols_ + c];
    }

}
