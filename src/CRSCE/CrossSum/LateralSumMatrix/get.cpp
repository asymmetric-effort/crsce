/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix/get.cpp
 * @brief declare the Lateral (lsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

/**
 * @name get
 * @memberof LateralSumMatrix
 * @brief return the value of row r
 * @param r CrossSumIndex
 * @return CrossSumValue
 */
CrossSumValue LateralSumMatrix::LateralSumMatrix::get(const CrossSumIndex r, const CrossSumIndex _) const {
    bounds_check(r);
    return data[r];
}
