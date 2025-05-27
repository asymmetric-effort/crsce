/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix/increment.cpp
 * @brief declare the Lateral (lsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

/**
 * @name increment
 * @memberof LateralSumMatrix
 * @brief increment the value for row r
 * @param r CrossSumIndex
 */
void LateralSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex _) {
    bounds_check(r);
    ++data[r];
}
