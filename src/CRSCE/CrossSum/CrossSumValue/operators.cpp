// file: src/CRSCE/CrossSum/CrossSumValue/operators.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

uint16_t CrossSumValue::to_uint16() const {
    return static_cast<uint16_t>(bits.to_ulong());
}

CrossSumValue CrossSumValue::operator+(uint16_t rhs) const {
    return CrossSumValue(this->to_uint16() + rhs);
}

// postfix
CrossSumValue& CrossSumValue::operator++() {
    *this = *this + 1;
    return *this;
}

// prefix
CrossSumValue CrossSumValue::operator++(int) {
    CrossSumValue temp = *this;
    ++(*this);
    return temp;
}
