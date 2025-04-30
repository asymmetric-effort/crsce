// file: src/CRSCE/CrossSum.CRSCE.destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include <iostream>
#include <stdexcept>

CRSCE::~CRSCE() {
    if (inputStream.is_open()) {
        inputStream.close();
    }
    if (outputStream.is_open()) {
        outputStream.close();
    }
}
