// file: include/Gpu/Math/Matrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <vector>
#include <cstddef>

namespace Gpu::Math {

    /**
     * @name Gpu::Math::Matrix
     * @brief Abstract base class for matrix-like structures.
     * @ref docs/Gpu/Design/Gpu-Math-Matrix.md
     */
    class Matrix {
    public:
        virtual ~Matrix() = default;

        virtual std::size_t rows() const noexcept = 0;
        virtual std::size_t cols() const noexcept = 0;

        virtual const double& at(std::size_t r, std::size_t c) const = 0;
        virtual double& at(std::size_t r, std::size_t c) = 0;

        virtual const std::vector<double>& data() const noexcept = 0;
        virtual std::vector<double>& data() noexcept = 0;
    };

} // namespace Gpu::Math
