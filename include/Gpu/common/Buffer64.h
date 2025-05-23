// file: include/Gpu/Common/Buffer64.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once
#include <vector>
#include <cstdint>

namespace Common {

    /**
     * @name Common::Buffer64
     * @brief A 64-bit aligned buffer used in the GPU abstraction layer for numeric operations.
     * @typedef Common::Buffer64
     * @ref docs/Gpu/Design/Common-Buffer64.md
     *
     * Buffer64 is a dynamic array of `uint64_t`. It is commonly used to store fixed-width values
     * in GPU memory transactions where 64-bit alignment is required.
     *
     * Typical use cases:
     * - Matrix operand storage
     * - Device memory interfaces using 64-bit words
     */
    using Buffer64 = std::vector<uint64_t>;

} // namespace Common
