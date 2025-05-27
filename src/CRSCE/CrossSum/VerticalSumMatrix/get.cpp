/**
 * @file include/CRSCE/CrossSum/VerticalSumMatrix/get.cpp
 * @brief declare the Vertical (VSM) Matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
/**
 * @name get
 * @class VerticalSumMatrix
 * @brief return the value at position c
 * @param _ CrossSumIndex
 * @param c CrossSumIndex
 * @return CrossSumValue
 */
CrossSumValue VerticalSumMatrix::VerticalSumMatrix::get(const CrossSumIndex _, const CrossSumIndex c) const {
    bounds_check(c);
    return data[c];
}
