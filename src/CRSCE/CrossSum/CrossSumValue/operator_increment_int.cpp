/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_increment_int.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

CrossSumValue CrossSumValue::operator++(int) {
    const CrossSumValue temp = *this;
    *this = *this + 1;
    return temp;
}
