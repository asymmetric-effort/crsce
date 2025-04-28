// file: include/CRSCE/CrossSumValueVerticalSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_VERTICAL_SUM_MATRIX_H
#define CRSCE_VERTICAL_SUM_MATRIX_H

#include "CRSCE/CrossSum/CrossSum.h"

class VerticalSumMatrix : public CrossSum {
public:

    explicit VerticalSumMatrix(const CrossSumIndex cross_sum_size,const CrossSumIndex cross_sum_width);

    ~VerticalSumMatrix();

    CrossSumValue get(CrossSumIndex _, CrossSumIndex c) const override;

    void set(CrossSumIndex _, CrossSumIndex c, CrossSumValue value) override;

    void increment(CrossSumIndex _, CrossSumIndex c) override;

};

#endif // CRSCE_VERTICAL_SUM_MATRIX_H

