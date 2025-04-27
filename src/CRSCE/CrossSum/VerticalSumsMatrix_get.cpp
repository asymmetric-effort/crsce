// file: include/CRSCE/CrossSum/VerticalSumsMatrix_get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/VerticalSumsMatrix.h"

VerticalSumsMatrix::VerticalSumsMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
