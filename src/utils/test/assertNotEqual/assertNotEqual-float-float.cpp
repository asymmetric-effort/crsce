/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-float-float.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that a should equal b
 * @param a float
 * @param b float
 * @param message std::string
 */
void Tester::assertNotEqual(const float a, const float b, const std::string& message) {
    if (constexpr double epsilon = 1e-9; std::abs(a - b) > epsilon) {
        pass(message);
    } else {
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
    }
}
