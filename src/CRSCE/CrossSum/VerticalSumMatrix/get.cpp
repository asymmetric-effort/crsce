// file: include/CRSCE/CrossSum/VerticalSumMatrix/get.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"

CrossSumValue VerticalSumMatrix::VerticalSumMatrix::get(const CrossSumIndex _, const CrossSumIndex c) const {
    return data[c];
}
