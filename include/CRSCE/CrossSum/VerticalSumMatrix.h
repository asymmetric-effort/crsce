// file: include/CRSCE/CrossSumValueVerticalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_VERTICAL_SUM_MATRIX_H
#define CRSCE_VERTICAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"

class VerticalSumMatrix : public CrossSum {
public:
    explicit VerticalSumMatrix(const CrossSumValue size);
    ~VerticalSumMatrix() override;

    CrossSumValue get(CrossSumValue r, CrossSumValue c) const override;
    void set(CrossSumValue r, CrossSumValue c, CrossSumValue value) override;
    void increment(CrossSumValue r, CrossSumValue c) override;
};

#endif // CRSCE_VERTICAL_SUM_MATRIX_H

