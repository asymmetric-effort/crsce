/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix/set.cpp
 * @brief declare the Lateral (lsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

/**
 * @name set
 * @memberof LateralSumMatrix
 * @brief increment the value for row r
 * @param r CrossSumIndex
 * @param c CrossSumIndex
 * @param value CrossSumValue
 */
void LateralSumMatrix::set(const CrossSumIndex r, const CrossSumIndex _, const CrossSumValue value) {
    bounds_check(r);
    data[r]=value;
}
