/**
 * @file src/CRSCE/CrossSum/CrossSumIndex/bounds_check.cpp
 * @brief Define the CRSCE CrossSumIndex
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"

/**
 * @name bounds_check
 * @brief perform a bounds check to insure the index is within the 0...s range.
 *        we should never have a cross sum index greater than s-1.
 * @param index CrossSumIndex
 */
void bounds_check(const CrossSumIndex index){
    if (index > max_index) {
        throw std::overflow_error("Index out of bounds");
    }
}
