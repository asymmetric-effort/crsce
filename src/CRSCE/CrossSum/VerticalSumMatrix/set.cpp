/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/set.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"

void VerticalSumMatrix::set(const CrossSumIndex _, const CrossSumIndex c, const CrossSumValue &value) {
    bounds_check(c);
    data[c]=value;
}
