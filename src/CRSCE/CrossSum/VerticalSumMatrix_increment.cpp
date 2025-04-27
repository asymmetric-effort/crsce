// file: include/CRSCE/CrossSum/VerticalSumMatrix_increment.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/VerticalSumMatrix.h"

VerticalSumMatrix::increment(const CrossSumIndex _, const CrossSumIndex c) const {
    data[c]++;
}
