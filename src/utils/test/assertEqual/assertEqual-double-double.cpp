/**
 * @file src/utils/test/assertEqual/assertEqual-double-double.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs Common::double
 * @param rhs Common::double
 * @param message std::string
 */
void Tester::assertEqual(const double lhs, const double rhs, const std::string& message) {
    if (constexpr double epsilon = 1e-9; std::abs(lhs - rhs) > epsilon) {
        fail("assertEqual<double> Failed: " + message);
    } else {
        pass(message);
    }
}
