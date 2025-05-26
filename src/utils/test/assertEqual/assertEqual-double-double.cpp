// file: src/utils/test/assertEqual/assertEqual-$i-$i.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(const double a, const double b, const std::string& message) {
    if (constexpr double epsilon = 1e-9; std::abs(a - b) > epsilon) {
        fail("assertEqual<double> Failed: " + message);
    } else {
        pass(message);
    }
}
