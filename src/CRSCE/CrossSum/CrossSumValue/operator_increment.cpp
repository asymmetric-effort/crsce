/**
 * @file src/CRSCE/CrossSum/CrossSumValue/operator_increment.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"

CrossSumValue &CrossSumValue::operator++() {
    *this = *this + 1;
    return *this;
}
