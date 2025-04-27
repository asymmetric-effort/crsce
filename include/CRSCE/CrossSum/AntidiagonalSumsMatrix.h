// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
#define CRSCE_ANTIDIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"
#include "utils/transformations/dsm.h"

class AntidiagonalSumMatrix : public CrossSum {
public:
    explicit AntidiagonalSumMatrix(const unsigned int size);
    ~AntidiagonalSumMatrix() override;

    unsigned int get(unsigned int r, unsigned int c) const override;
    void set(unsigned int r, unsigned int c, unsigned int value) override;
    void increment(unsigned int r, unsigned int c) override;
};

#endif // CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
