/**
 * @file src/utils/test/assertEqual/assertEqual-float-float.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs float
 * @param rhs float
 * @param message std::string
 */
void Tester::assertEqual(const float lhs, const float rhs, const std::string& message) {
    if (constexpr float epsilon = 1e-1f; std::abs(lhs - rhs) > epsilon) {
        fail("assertEqual<float> Failed: " + message);
    } else {
        pass(message);
    }
}
