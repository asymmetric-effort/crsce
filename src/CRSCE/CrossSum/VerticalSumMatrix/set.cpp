/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/set.cpp
 * @brief declare the Vertical (VSM) Matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
/**
 * @name set
 * @class VerticalSumMatrix
 * @brief set the value at position c
 * @param _ CrossSumIndex
 * @param c CrossSumIndex
 * @param value CrossSumValue
 */
void VerticalSumMatrix::set(const CrossSumIndex _, const CrossSumIndex c, const CrossSumValue v) {
    bounds_check(c);
    data[c]=v;
}
