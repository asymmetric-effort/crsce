// file: include/CRSCE/CrossSum/LateralSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LATERAL_SUM_MATRIX_H
#define CRSCE_LATERAL_SUM_MATRIX_H

#include "CRSCE/CrossSum/CrossSum.h"

class LateralSumMatrix : public CrossSum {
public:

    explicit LateralSumMatrix(const CrossSumIndex size,const CrossSumIndex width);

    ~LateralSumMatrix();

    CrossSumValue get(CrossSumIndex r, CrossSumIndex _) const override;

    void set(CrossSumIndex r, CrossSumIndex _, CrossSumValue value);

    void increment(CrossSumIndex r, CrossSumIndex _);

};

#endif // CRSCE_LATERAL_SUM_MATRIX_H
