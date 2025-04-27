// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix_get.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/AntidiagonalSumMatrix.h"

CrossSumValue AntidiagonalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return data[transform(r,c)];
}
