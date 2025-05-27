/**
 * @file include/CRSCE/CrossSum/CrossSumIndex.h
 * @brief Declare the 16-bit CrossSumIndex type and its bounds_check() function.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_CROSS_SUM_INDEX_H
#define CRSCE_CROSS_SUM_INDEX_H

#include "CRSCE/constants/constants.h"
#include <stdexcept>
#include <cstdint>

/**
 * @name CrossSumIndex
 * @brief An unsigned 16-bit integer representing the index of a cross sum matrix (0,...,s-1).
 */
using CrossSumIndex = uint16_t;
/**
 * @name bounds_check
 * @brief perform a bounds check to insure the index is within the 0...s range.
 *        we should never have a cross sum index greater than s-1.
 * @param index CrossSumIndex
 */
void bounds_check(const CrossSumIndex index);

#endif // CRSCE_CROSS_SUM_INDEX_H
