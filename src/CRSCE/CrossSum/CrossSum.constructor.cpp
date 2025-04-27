// file: include/CRSCE/CrossSum/CrossSum.constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/CrossSum.h"

CrossSum::CrossSum(const CrossSumValue size, const CrossSumValue width)
    : s(size), w(width), data(size, 0) {

      // Initialize vector with 'size' elements all zeroed.

}
