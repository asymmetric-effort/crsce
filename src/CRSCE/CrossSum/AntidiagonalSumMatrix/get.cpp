/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix/get.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

CrossSumValue AntidiagonalSumMatrix::get(const CrossSumIndex r, const CrossSumIndex c) const {
    return this->storage()[transform(r,c)];
}
