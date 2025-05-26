// file: src/utils/test/assertEqual/assertEqual-$i-$i.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(float a, float b, const std::string& message) {
    constexpr float epsilon = 1e-5f;
    if (std::abs(a - b) > epsilon) {
        fail("assertEqual<float> Failed: " + message);
    } else {
        pass(message);
    }
}
