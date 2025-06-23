/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/increment.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"

void DiagonalSumMatrix::increment(const CrossSumIndex r, const CrossSumIndex c) {
    ++this->storage()[transform(r,c)];
}
