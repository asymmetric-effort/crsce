// file: include/CRSCE/CrossSum.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#ifndef CRSCE_CROSSSUM_H
#define CRSCE_CROSSSUM_H

#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <vector>
#include <cstdint>

class CrossSum {
public:

    explicit CrossSum(const CrossSumIndex cross_sum_size, const CrossSumIndex cross_sum_width);

    ~CrossSum();

    virtual CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const;

    virtual void set(CrossSumIndex r, CrossSumIndex c, CrossSumValue value);

    virtual void increment(CrossSumIndex r, CrossSumIndex c);

protected:

    const CrossSumIndex s;
    const CrossSumIndex b;

    std::vector<CrossSumValue> data;

};

#endif // CRSCE_CROSSSUM_H
