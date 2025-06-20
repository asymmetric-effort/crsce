/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_plus_uint16_t.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>

CrossSumValue CrossSumValue::operator+(const uint16_t rhs) const {
    uint16_t lhs = this->to_uint16();
    if (lhs > s || rhs > s || lhs + rhs > s) {
        throw std::overflow_error("Value out of bounds");
    }
    return CrossSumValue(lhs + rhs);
}
