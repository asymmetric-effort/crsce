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

    explicit CrossSum(const CrossSumIndex size,const CrossSumIndex width);

    ~CrossSum();

    virtual CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const;

    virtual void set(CrossSumValue r, CrossSumValue c, CrossSumValue value);

    virtual void increment(CrossSumValue r, CrossSumValue c);

protected:

    const CrossSumValue s;

    std::vector<CrossSumValue> data;

};

#endif // CRSCE_CROSSSUM_H
