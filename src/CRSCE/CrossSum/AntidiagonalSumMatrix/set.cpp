// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix/set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

void AntidiagonalSumMatrix::set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) {
    data[transform(r,c)]=v;
}
