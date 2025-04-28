// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix/get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

CrossSumValue AntidiagonalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
