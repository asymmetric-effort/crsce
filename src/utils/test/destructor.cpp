// file: src/utils/test/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

// Construct with a test prefix
Tester::~Tester() {

    std::cerr <<
        "[" << prefix << "] Tester tear-down: " << std::endl
        << " Pass: " << passScore << std::endl
        << " Fail: " << failScore << std::endl
        << "Total: " << (passScore + failScore) << std::endl
        << std::endl;

}
