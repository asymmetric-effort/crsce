// file: include/Gpu/Math/Matrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

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
         * @name at
         * @brief return the value at position r,c
         * @param r
         * @param c
         * @return const double
         */
        const double& at(std::size_t r, std::size_t c) const;
        /**
         * @name at
         * @brief return the value at position r,c
         * @param r
         * @param c
         * @return double
         */
        double& at(std::size_t r, std::size_t c);
        /**
         * @name data
         * @brief serialize the matrix as a vector of double values
         * @return const vector<double>
         */
        const std::vector<double>& data() const noexcept;
        /**
         * @name data
         * @brief serialize the matrix as a vector of double values
         * @return vector<double>
         */
        std::vector<double>& data() noexcept;

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> buffer_;
    };

} // namespace Gpu::Math
