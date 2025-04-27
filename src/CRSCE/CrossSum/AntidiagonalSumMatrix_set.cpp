// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix_set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/AntidiagonalSumMatrix.h"

AntidiagonalSumMatrix::set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) const {
    data[transform(r,c)]=v;
}
