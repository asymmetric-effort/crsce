// file: src/CRSCE/CrossSum/CrossSumValue/operator_plusplus_int.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSumValue.h"

CrossSumValue CrossSumValue::operator++(int) {
    CrossSumValue temp = *this;
    ++(*this);
    return temp;
}
