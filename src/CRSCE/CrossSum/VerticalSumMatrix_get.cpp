// file: include/CRSCE/CrossSum/VerticalSumMatrix_get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/VerticalSumMatrix.h"

VerticalSumMatrix::VerticalSumMatrix::get(const CrossSumIndex _, const CrossSumIndex c) const {
    return data[c];
}
