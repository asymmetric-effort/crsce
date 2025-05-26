/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/increment.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

void AntidiagonalSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) {
    data[transform(r,c)]++;
}
