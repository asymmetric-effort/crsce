// file: include/Gpu/Math/Matrix2D.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include "Gpu/Math/Matrix.h"

namespace Gpu::Math {

    /**
     * @name Gpu::Math::Matrix2D
     * @brief Dense row-major 2D matrix implementation.
     * @ref docs/Gpu/Design/Gpu-Math-Matrix.md
     */
    class Matrix2D final : public Matrix {
    public:
        Matrix2D(std::size_t rows, std::size_t cols);

        std::size_t rows() const noexcept override;
        std::size_t cols() const noexcept override;

        const double& at(std::size_t r, std::size_t c) const override;
        double& at(std::size_t r, std::size_t c) override;

        const std::vector<double>& data() const noexcept override;
        std::vector<double>& data() noexcept override;

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> buffer_;
    };

} // namespace Gpu::Math
