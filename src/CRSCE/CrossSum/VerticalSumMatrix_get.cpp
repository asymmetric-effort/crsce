// file: include/CRSCE/CrossSum/VerticalSumMatrix_get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/VerticalSumMatrix.h"

VerticalSumMatrix::VerticalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
