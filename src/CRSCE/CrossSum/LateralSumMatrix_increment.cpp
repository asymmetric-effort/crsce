// file: include/CRSCE/CrossSum/LateralSumMatrix_increment.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LateralSumMatrix.h"

LateralSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex _) const {
    data[r]++;
}
