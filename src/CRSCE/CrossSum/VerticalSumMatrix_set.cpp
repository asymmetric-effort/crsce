// file: include/CRSCE/CrossSum/VerticalSumMatrix_set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/VerticalSumMatrix.h"

VerticalSumMatrix::set(const CrossSumValue _, const CrossSumIndex c, const CrossSumValue v) const {
    data[c]=v;
}
