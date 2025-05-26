/**
 * @file include/CRSCE/CrossSum/AntidiagonalSumMatrix.h
 * @brief declare the Anti-diagonal (xsm) matrix class
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
#define CRSCE_ANTIDIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum/CrossSum.h"

class AntidiagonalSumMatrix final : public CrossSum {
public:

    explicit AntidiagonalSumMatrix();

    ~AntidiagonalSumMatrix() override;

    CrossSumValue get(const CrossSumIndex r, const CrossSumIndex c) const override;

    void set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) override;

    void increment(const CrossSumIndex r, const CrossSumIndex c) override;

    CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c) const;
};

#endif // CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
