/**
 * @file src/CRSCE/CrossSum/CrossSumIndex/bounds_check.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"

void bounds_check(const CrossSumIndex index){
    if (index > max_index) {
        throw std::overflow_error("Index out of bounds");
    }
}
