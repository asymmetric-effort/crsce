/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/get.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"

CrossSumValue VerticalSumMatrix::get(const CrossSumIndex _, const CrossSumIndex c) const {
    bounds_check(c);
    return this->storage()[c];
}
