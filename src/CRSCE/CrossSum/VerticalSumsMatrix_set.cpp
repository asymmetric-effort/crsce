// file: include/CRSCE/CrossSum/VerticalSumsMatrix_set.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/VerticalSumsMatrix.h"

VerticalSumsMatrix::set(const CrossSumValue r, const CrossSumIndex c, const CrossSumValue v) const {
    data[transform(r,c)]=v;
}
