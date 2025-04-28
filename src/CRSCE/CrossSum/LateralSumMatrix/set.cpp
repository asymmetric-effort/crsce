// file: include/CRSCE/CrossSum/LateralSumMatrix/set.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"

void LateralSumMatrix::set(const CrossSumValue r, const CrossSumIndex _, const CrossSumValue v) {
    data[r]=v;
}
