// file: src/Gpu/Math/Matrix/data.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Math/Matrix.h"

namespace Gpu::Math {

    const std::vector<double>& Matrix::data() const noexcept {
        return buffer_;
    }

}
