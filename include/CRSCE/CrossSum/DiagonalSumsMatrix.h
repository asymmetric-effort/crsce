// file: include/CRSCE/CrossSum/DiagonalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_DIAGONAL_SUM_MATRIX_H
#define CRSCE_DIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"
#include "utils/transformations/xsm.h"

class DiagonalSumMatrix : public CrossSum {
public:
    explicit DiagonalSumMatrix(const unsigned int size);
    ~DiagonalSumMatrix() override;

    unsigned int get(unsigned int r, unsigned int c) const override;
    void set(unsigned int r, unsigned int c, unsigned int value) override;
    void increment(unsigned int r, unsigned int c) override;
};

#endif // CRSCE_DIAGONAL_SUM_MATRIX_H

