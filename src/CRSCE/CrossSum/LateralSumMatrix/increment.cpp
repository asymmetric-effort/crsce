// file: include/CRSCE/CrossSum/LateralSumMatrix/increment.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

void LateralSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex _) {
    bounds_check(r,s);
    data[r]++;
}
