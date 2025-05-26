/**
 * @file include/Gpu/Math/Matrix.h
 * @brief Declare a concrete two-dimensional matrix of double-precision floats where operations are performed on
 *        the GPU.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <vector>
#include <cstddef>

namespace Gpu::Math {

    /**
     * @name Gpu::Math::Matrix
     * @brief Concrete row-major 2D matrix of double-precision floats.
     * @ref docs/Gpu/Design/Gpu-Math-Matrix.md
     */
    class Matrix {
    public:
        /**
         * @name constructor
         * @brief initialize the matrix size.
         * @param rows
         * @param cols
         */
        Matrix(std::size_t rows, std::size_t cols);

        /**
         * @name rows
         * @brief return the number of rows
         * @return size_t
         */
        std::size_t rows() const noexcept;

        /**
         * @name cols
         * @brief return the number of columns
         * @return size_t
         */
        std::size_t cols() const noexcept;
        /**
         * @name at (mutable)
         * @brief return the value at position r,c
         * @param r
         * @param c
         * @return const double
         */
        double& at(std::size_t r, std::size_t c);
        /**
         * @name at (constant)
         * @brief return the value at position r,c
         * @param r
         * @param c
         * @return const double
         */
        const double& at(std::size_t r, std::size_t c) const;
        /**
         * @name data (mutable)
         * @brief serialize the matrix as a vector of double values
         * @return const vector<double>
         */
        std::vector<double>& data() noexcept;
        /**
         * @name data (const)
         * @brief serialize the matrix as a vector of double values
         * @return const vector<double>
         */
        const std::vector<double>& data() const noexcept;

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> buffer_;
    };

} // namespace Gpu::Math
