// file: include/CRSCE/CrossSum/DiagonalSumMatrix_set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/DiagonalSumMatrix.h"

DiagonalSumMatrix::set(const CrossSumValue r, const CrossSumIndex c, const CrossSumValue v) const {
    data[transform(r,c)]=v;
}
