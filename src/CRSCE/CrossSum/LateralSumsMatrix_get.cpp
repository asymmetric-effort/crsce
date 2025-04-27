// file: include/CRSCE/CrossSum/LateralSumsMatrix_get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/LateralSumsMatrix.h"

LateralSumsMatrix::LateralSumsMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
