// file: include/Gpu/Math/Matrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <vector>
#include <cstddef>
#include <cstdint>

namespace Gpu::Math {

    /**
     * @name Gpu::Math::Matrix
     * @brief Represents a dense 2D matrix of 64-bit values stored in row-major order.
     * @ref docs/Gpu/Design/Gpu-Math-Matrix.md
     */
    class Matrix {
    public:
        Matrix(std::size_t rows, std::size_t cols);
        std::size_t rows() const noexcept;
        std::size_t cols() const noexcept;

        const uint64_t& at(std::size_t r, std::size_t c) const;
        uint64_t& at(std::size_t r, std::size_t c);

        const std::vector<uint64_t>& data() const noexcept;
        std::vector<uint64_t>& data() noexcept;

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<uint64_t> buffer_;
    };

} // namespace Gpu::Math
