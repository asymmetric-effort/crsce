// file: src/utils/test/assertFalse.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert a condition; on failure, print message and terminate
void Tester::assertFalse(bool condition, const std::string& message) {
    if (!condition) {
        pass(std::format("ok: {}", message));
    }else{
        Tester::fail(std::format("assertFalse() failed: {}", message));
    }
}
