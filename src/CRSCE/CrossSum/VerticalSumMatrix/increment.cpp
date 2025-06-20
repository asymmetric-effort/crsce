/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/increment.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"

void VerticalSumMatrix::increment(const CrossSumIndex _, const CrossSumIndex c) {
    bounds_check(c);
    ++this->storage()[c];
}
