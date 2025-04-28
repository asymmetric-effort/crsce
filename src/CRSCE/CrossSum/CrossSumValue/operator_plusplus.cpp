// file: src/CRSCE/CrossSum/CrossSumValue/operator_plusplus.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSumValue.h"

CrossSumValue& CrossSumValue::operator++() {
    *this = *this + 1;
    return *this;
}
