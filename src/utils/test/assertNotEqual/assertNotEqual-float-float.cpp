/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-float-float.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that lhs should not equal rhs
 * @param lhs float
 * @param rhs float
 * @param message std::string
 */
void Tester::assertNotEqual(const float lhs, const float rhs, const std::string& message) {
    if (constexpr double epsilon = 1e-9; std::abs(lhs - rhs) > epsilon) {
        pass(message);
    } else {
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
    }
}
