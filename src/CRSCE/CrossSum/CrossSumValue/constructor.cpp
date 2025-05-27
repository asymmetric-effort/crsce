/**
 * @file src/CRSCE/CrossSum/CrossSumValue/constructor.cpp
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

/**
 * @name constructor
 * @class CrossSumValue
 * @brief initialize the class state
 */
CrossSumValue::CrossSumValue() : bits(0) {}

/**
 * @name constructor
 * @class CrossSumValue
 * @brief initialize the class state
 * @param value uint16_t : number of bits in the value
 */
CrossSumValue::CrossSumValue(uint16_t value) {
    if (value >= (1u << b)) {
        throw std::out_of_range("CrossSumValue exceeds allowed bit width");
    }
    bits = std::bitset<b>(value);
}
