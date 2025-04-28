// file: src/CRSCE/CrossSum/CrossSumValue/operators.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

uint16_t CrossSumValue::to_uint16() const {
    return static_cast<uint16_t>(bits.to_ulong());
}

CrossSumValue CrossSumValue::operator+(uint16_t rhs) const {
    auto result= CrossSumValue(this->to_uint16() + rhs);
    if(this->to_uint16() > max_value) throw std::overflow_error("CrossSumValue overflow");
    return result;
}

// postfix
CrossSumValue& CrossSumValue::operator++() {
    *this = *this + 1;
    if(this->to_uint16() > max_value) throw std::overflow_error("CrossSumValue overflow");
    return *this;
}

// prefix
CrossSumValue CrossSumValue::operator++(int) {
    CrossSumValue temp = *this;
    ++(*this);
    if(this->to_uint16() > max_value) throw std::overflow_error("CrossSumValue overflow");
    return temp;
}
