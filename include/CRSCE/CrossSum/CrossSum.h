/**
 * @file include/CRSCE/CrossSum.h
 * @brief Declare the pure virtual CrossSum parent class for LSM, VSM, DSM and XSM.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_CROSSSUM_H
#define CRSCE_CROSSSUM_H

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <vector>
#include <cstdint>

class CrossSum {
public:

    //constructor : initialize a cross sum matrix with constants s and b.
    explicit CrossSum();

    virtual ~CrossSum();

    virtual CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const;

    virtual void set(CrossSumIndex r, CrossSumIndex c, CrossSumValue value);

    virtual void increment(CrossSumIndex r, CrossSumIndex c);

    void serialize(std::ostream& os) const;

protected:

    std::vector<CrossSumValue> data;

};

#endif // CRSCE_CROSSSUM_H
