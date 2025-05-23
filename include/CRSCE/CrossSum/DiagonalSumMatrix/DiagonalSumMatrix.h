// file: include/CRSCE/CrossSum/DiagonalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_DIAGONAL_SUM_MATRIX_H
#define CRSCE_DIAGONAL_SUM_MATRIX_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSum.h"

class DiagonalSumMatrix : public CrossSum {
public:

    explicit DiagonalSumMatrix();

    ~DiagonalSumMatrix();

    CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const override;

    void set(CrossSumIndex r, CrossSumIndex c, CrossSumValue value) override;

    void increment(CrossSumIndex r, CrossSumIndex c) override;

    CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c) const;
};

#endif // CRSCE_DIAGONAL_SUM_MATRIX_H

