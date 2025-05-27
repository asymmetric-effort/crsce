/**
 * @file include/CRSCE/CrossSum.h
 * @brief Declare the pure virtual CrossSum parent class for LSM, VSM, DSM and XSM.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_CROSSSUM_H
#define CRSCE_CROSSSUM_H

#include "CRSCE/CRSCE.h"
#include "CRSCE/FileBuffer.h"
#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <vector>
#include <cstdint>
#include <cstdint>
#include <ostream>
#include <bitset>

class CrossSum {
public:
    /**
     * @name constructor
     * @brief initialize state (s)
     */
    explicit CrossSum();

    /**
     * @name destructor
     * @brief clear and reset the state
     */
    virtual ~CrossSum();

    /**
     * @name get
     * @brief return the cross sum value at position (r,c).
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @return CrossSumValue
     */
    virtual CrossSumValue get(CrossSumIndex r, CrossSumIndex c) const;

    /**
     * @name set
     * @brief set the value at position (r,c).
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @param value CrossSumValue
     */
    virtual void set(CrossSumIndex r, CrossSumIndex c, CrossSumValue value);

    /**
     * @name increment
     * @brief increment the cross sum value at position (r,c).
     * @param r CrossSumIndex
     * @param c CrossSumIndex
     * @return CrossSumValue
     */
    virtual void increment(CrossSumIndex r, CrossSumIndex c);

    /**
     * @name serialize
     * @brief serialize the cross sum matrix as a packed array of b-bit elements
     * @param os std::ostream&
     */
    void serialize(std::ostream &os) const;

protected:
    /**
     * @property data
     * @brief a vector of CrossSumValue represents a single cross-sum value.
     */
    std::vector<CrossSumValue> data;
};

#endif // CRSCE_CROSSSUM_H
