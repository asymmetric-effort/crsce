// file: include/CRSCE/CrossSum/VerticalSumMatrix/set.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"

void VerticalSumMatrix::set(const CrossSumValue _, const CrossSumIndex c, const CrossSumValue v) {
    data[c]=v;
}
