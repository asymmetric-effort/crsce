// file: src/utils/test/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

// Construct with a test prefix
Tester::~Tester() {
    showStatistics();
    if(failScore > 0) exit(1);
}
