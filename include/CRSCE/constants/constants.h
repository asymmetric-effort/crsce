/**
 * @file include/CRSCE/constants/constants.h
 * @brief defines CRSCE constants
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <cstddef>
#include <string>

// Matrix dimensions : ToDo these should be configurable by CLI
/**
 * @name s
 * @brief The matrix size parameter representing the length and width of the square CSM matrix and the length of
 *        the one-dimensional cross sum matrices.
 * @todo We should make this configurable with --block-size for compression or by reading compressed input.
 */
constexpr size_t s = 512 - 1; // 511
/**
 * @name max_index
 * @brief The max index based on S, where max_index is always s-1 since the index is {0...s-1}
 * @todo This should be determined by a configurable s-value.
 */
constexpr size_t max_index = s - 1; // 510
/**
 * @name b
 * @brief The width of a cross-sum matrix element.
 * @todo This should be determined by a configurable s-value.
 */
constexpr size_t b = 9; // ceil(log2(s + 1))

/**
 * @name HEADER
 * @brief  File header used as MAGIC to indicate CRSCE compressed file output.
 */
const std::string HEADER = "CRSCE";
