/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/increment.cpp
 * @brief declare the Vertical (VSM) Matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
/**
 * @name increment
 * @class VerticalSumMatrix
 * @brief increment the VSM[c] value
 * @param _
 * @param c
 */
void VerticalSumMatrix::increment(const CrossSumIndex _, const CrossSumIndex c) {
    bounds_check(c);
    ++data[c];
}
