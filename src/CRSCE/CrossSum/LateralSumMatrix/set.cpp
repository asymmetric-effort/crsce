// file: include/CRSCE/CrossSum/LateralSumMatrix/set.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

void LateralSumMatrix::set(const CrossSumIndex r, const CrossSumIndex _, const CrossSumValue v) {
    bounds_check(r,s);
    data[r]=v;
}
