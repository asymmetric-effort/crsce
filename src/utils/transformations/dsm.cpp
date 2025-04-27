// file: src/utils/transformations/dsm.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/transformations/dsm.h"

unsigned int dsm(unsigned int r, unsigned int c, unsigned int s) {
    return (r + s - c) % s;
}
