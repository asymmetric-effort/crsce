// file: src/utils/test/assertTrue.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert a condition; on failure, print message and terminate
void Tester::assertTrue(bool condition, const std::string& message) {
    if (condition) {
        Tester::pass();
    }else{
        std::cerr << "[" << prefix << "](FAIL) Assertion failed: " << message << std::endl;
        Tester::fail();
    }
}
