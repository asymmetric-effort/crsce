// file: include/CRSCE/CrossSum/LateralSumMatrix.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_LATERAL_SUM_MATRIX_H
#define CRSCE_LATERAL_SUM_MATRIX_H

#include "CRSCE/CrossSum.h"

class LateralSumMatrix : public CrossSum {
public:
    explicit LateralSumMatrix(const unsigned int size);
    ~LateralSumMatrix() override;

    unsigned int get(unsigned int r, unsigned int c) const override;
    void set(unsigned int r, unsigned int c, unsigned int value) override;
    void increment(unsigned int r, unsigned int c) override;
};

#endif // CRSCE_LATERAL_SUM_MATRIX_H
