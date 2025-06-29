/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-int-int.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that lhs should not equal rhs
 * @param lhs int
 * @param rhs int
 * @param message std::string
 */
void Tester::assertNotEqual(const int lhs, const int rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
