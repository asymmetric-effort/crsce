/**
 * @file include/CRSCE/CrossSum/DiagonalSumMatrix/set.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"

void DiagonalSumMatrix::set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue &value) {
    this->storage()[transform(r,c)]=value;
}
