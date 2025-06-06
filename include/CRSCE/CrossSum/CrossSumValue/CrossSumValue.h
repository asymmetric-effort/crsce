/**
 * @file include/CRSCE/CrossSumValue.h
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef CRSCE_CROSSSUM_VALUE_H
#define CRSCE_CROSSSUM_VALUE_H

#include "CRSCE/constants/constants.h"
#include <bitset>
#include <cstdint>
#include <stdexcept>

/**
 * @class CrossSumValue
 * @brief The value of a cross sum (0,...,s)
 */
class CrossSumValue {
public:
    /**
     * @name constructor
     * @brief initialize the class state
     * @class CrossSumValue
     */
    CrossSumValue();
    /**
     * @name constructor
     * @brief initialize the class state
     * @class CrossSumValue
     * @param value uint16_t : number of bits in the value
     */
    explicit CrossSumValue(uint16_t value);
    /**
     * @name destructor
     * @brief default
     * @class CrossSumValue
     */
    ~CrossSumValue()=default;

    /**
     * @name to_uint16
     * @brief return the uint16 value representation of the internal state.
     */
    uint16_t to_uint16() const;
    /**
     * @name operator+
     * @param rhs uint16_6
     * @return CrossSumValue
     */
    CrossSumValue operator+(uint16_t rhs) const;
    /**
     * @name operator+
     * @param rhs CrossSumValue
     * @return CrossSumValue
     */
    CrossSumValue operator+(CrossSumValue rhs) const;
    /**
     * @name operator++
     * @return CrossSumValue
     */
    CrossSumValue& operator++();
    /**
     * @name operator++
     * @return int
     */
    CrossSumValue operator++(int);
private:
    std::bitset<b> bits;
};

#endif // CRSCE_CROSSSUM_VALUE_H
