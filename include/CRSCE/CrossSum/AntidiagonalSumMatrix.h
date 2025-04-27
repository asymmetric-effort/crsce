// file: include/CRSCE/CrossSum/AntidiagonalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
#define CRSCE_ANTIDIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"
#include "utils/transformations/dsm.h"

class AntidiagonalSumMatrix : public CrossSum {
public:
    explicit AntidiagonalSumMatrix(const CrossSumValue size);
    ~AntidiagonalSumMatrix() override;

    CrossSumValue get(const CrossSumIndex r, const CrossSumIndex c) const override;
    void set(const CrossSumIndex r, const CrossSumIndex c, const CrossSumValue v) override;
    void increment(const CrossSumIndex r, const CrossSumIndex c) override;
private:
    CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c) const;
};


#endif // CRSCE_ANTIDIAGONAL_SUM_MATRIX_H
