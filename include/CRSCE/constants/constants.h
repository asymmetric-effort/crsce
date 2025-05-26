/**
 * @file include/CRSCE/constants/constants.h
 * @brief defines CRSCE constants
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#ifndef CRSCE_CONSTANTS_H
#define CRSCE_CONSTANTS_H

#include <cstddef>
#include <cstdint>

// Matrix dimensions
constexpr size_t s = 512 - 1;          // 511
constexpr size_t max_index = s - 1;    // 510
constexpr size_t b = 9;                // ceil(log2(s + 1))

// File header
constexpr std::size_t HEADER_LENGTH = 5;
constexpr char HEADER[HEADER_LENGTH] = { 'C', 'R', 'S', 'C', 'E' };

#endif // CRSCE_CONSTANTS_H
