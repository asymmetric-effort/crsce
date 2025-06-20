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

    ~AntidiagonalSumMatrix() override =default;

    [[nodiscard]] CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const override;

    void set(CrossSumIndex r, CrossSumIndex c, const CrossSumValue &value) override;

    void increment(CrossSumIndex r, CrossSumIndex c) override;

    [[nodiscard]] static CrossSumIndex transform(CrossSumIndex r, CrossSumIndex c);
};

#endif // CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
