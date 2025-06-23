/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_plus_CrossSumValue.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

CrossSumValue operator+(const CrossSumValue& lhs, const CrossSumValue& rhs) {
    const uint16_t l = lhs.to_uint16();
    const uint16_t r = rhs.to_uint16();
    if (l > s || r > s || static_cast<uint32_t>(l) + r > s) {
        throw std::overflow_error("CrossSumValue addition overflow");
    }
    return CrossSumValue(static_cast<uint16_t>(l + r));
}
