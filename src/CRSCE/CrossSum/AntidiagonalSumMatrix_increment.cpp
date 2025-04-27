// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix_increment.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/AntidiagonalSumsMatrix.h"

AntidiagonalSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) const {
    data[transform(r,c)]++;
}
