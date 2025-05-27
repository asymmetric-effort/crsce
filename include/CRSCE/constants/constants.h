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
/**
 * @name s
 * @brief The CRSCE s-value is the size (length and width), in bits, of the CSM matrix representing uncompressed data.
 *        At present, we hard-code this value as 511 bits.
 */
constexpr size_t s = 512 - 1;          // 511
/**
 * @name max_index
 * @brief The maximum index of a cross sum, where the range is 0,...510.
 */
constexpr size_t max_index = s - 1;    // 510
/**
 * @name b
 * @brief the width of the cross sum in bits, calculated as the ceiling of the base-2 logarithm of s.
 *
 *          b=ceil(log2(s + 1))
 *          b=ceil(log2(511+1))
 *          b=ceil(log2(512))
 *          b=ceil(9)
 *          b=9
 */
constexpr size_t b = 9;
/**
 * @name HEADER_LENGTH
 * @brief This is the length of the file header.
 */
constexpr std::size_t HEADER_LENGTH = 5;
/**
 * @name HEADER
 * @brief The header string for CRSCE compressed files.
 */
constexpr char HEADER[HEADER_LENGTH] = { 'C', 'R', 'S', 'C', 'E' };

#endif // CRSCE_CONSTANTS_H
