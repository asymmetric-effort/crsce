// file: include/CRSCE/CrossSum/DiagonalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_DIAGONAL_SUM_MATRIX_H
#define CRSCE_DIAGONAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"
#include "utils/transformations/xsm.h"

class DiagonalSumMatrix : public CrossSum {
public:
    explicit DiagonalSumMatrix(const CrossSumValue size);
    ~DiagonalSumMatrix() override;

    CrossSumValue get(CrossSumValue r, CrossSumValue c) const override;
    void set(CrossSumValue r, CrossSumValue c, CrossSumValue value) override;
    void increment(CrossSumValue r, CrossSumValue c) override;
private:
    CrossSumIndex transform(const CrossSumIndex r, const CrossSumIndex c) const;
};

#endif // CRSCE_DIAGONAL_SUM_MATRIX_H

