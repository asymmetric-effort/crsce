/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_plus_uint16_t.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <stdexcept>


CrossSumValue operator+(const CrossSumValue& lhs, const uint16_t rhs) {
    const uint16_t l = lhs.to_uint16();
    if (l > s || rhs > s || static_cast<uint32_t>(l) + rhs > s) {
        throw std::overflow_error("CrossSumValue addition overflow");
    }
    return CrossSumValue(static_cast<uint16_t>(l + rhs));
}
