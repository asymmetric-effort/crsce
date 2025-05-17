// file: src/utils/test/destructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

// Construct with a test prefix
Tester::~Tester() {

    std::cerr <<
        "[" << prefix << "] Tester tear-down: " << std::endl
        << " Pass: " << pass_score << std::endl
        << " Fail: " << fail_score << std::endl
        << "Total: " << (pass_score + fail_score) << std::endl
        << std::endl;

}
