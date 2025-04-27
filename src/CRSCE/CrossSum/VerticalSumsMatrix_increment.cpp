// file: include/CRSCE/CrossSum/VerticalSumsMatrix_increment.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/VerticalSumsMatrix.h"

VerticalSumsMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) const {
    data[transform(r,c)]++;
}
