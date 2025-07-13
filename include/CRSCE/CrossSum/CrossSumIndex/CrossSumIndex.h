/**
 * @file include/CRSCE/CrossSum/CrossSumIndex.h
 * @brief Declare the 16-bit CrossSumIndex type and its bounds_check() function.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include <cstdint>

/**
 * @name CrossSumIndex
 * @brief we should never have a cross sum index greater than s-1 (max_index).
 */
using CrossSumIndex = uint16_t;

/**
 * @name bounds_check
 * @brief Verify the given index is not out of bounds
 * @param index CrossSumIndex
 */
inline void bounds_check(const CrossSumIndex index) {
    if (index > max_index) {
        throw std::overflow_error("Index out of bounds");
    }
}
