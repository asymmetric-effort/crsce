/**
 * @file include/CRSCE/CrossSum/LateralSumMatrix/set.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

void LateralSumMatrix::set(const CrossSumIndex r, const CrossSumIndex _, const CrossSumValue &value) {
    bounds_check(r);
    this->storage()[r]=value;
}
