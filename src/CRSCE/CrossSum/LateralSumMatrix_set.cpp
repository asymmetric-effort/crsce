// file: include/CRSCE/CrossSum/LateralSumMatrix_set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LateralSumMatrix.h"

LateralSumMatrix::set(const CrossSumValue r, const CrossSumIndex _, const CrossSumValue v) const {
    data[r]=v;
}
