/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix/get.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

CrossSumValue LateralSumMatrix::LateralSumMatrix::get(const CrossSumIndex r, const CrossSumIndex _) const {
    bounds_check(r);
    return data[r];
}
