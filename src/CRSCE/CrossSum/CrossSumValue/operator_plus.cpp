/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_plus.cpp
 * @brief Declare the CrossSumValue type as a 16-bit value and its operators.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

/**
 * @name operator+
 * @param rhs CrossSumValue
 * @return CrossSumValue
 */
CrossSumValue CrossSumValue::operator+(const uint16_t rhs) const {
    const uint16_t lhs = this->to_uint16();
    if (lhs > s || rhs > s || lhs + rhs > s) {
        throw std::overflow_error("Value out of bounds");
    }
    return CrossSumValue(lhs + rhs);
}

/**
 * @name operator+
 * @param rhs uint16_6
 * @return CrossSumValue
 */
CrossSumValue CrossSumValue::operator+(const CrossSumValue rhs) const {
    return *this + rhs.to_uint16();
}
