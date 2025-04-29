// file: src/CRSCE/CrossSum/CrossSumIndex/bounds_check.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSum/CrossSumIndex/CrossSumIndex.h"

void bounds_check(const CrossSumIndex index, const CrossSumIndex max_value){
    if (index >= max_value-1) {
        throw std::overflow_error("Index out of bounds");
    }
}