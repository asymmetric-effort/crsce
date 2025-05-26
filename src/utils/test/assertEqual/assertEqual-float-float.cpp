/**
 * @file src/utils/test/assertEqual/assertEqual-float-float.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a float
 * @param b float
 * @param message std::string
 */
void Tester::assertEqual(const float a, const float b, const std::string& message) {
    if (constexpr float epsilon = 1e-1f; std::abs(a - b) > epsilon) {
        fail("assertEqual<float> Failed: " + message);
    } else {
        pass(message);
    }
}
