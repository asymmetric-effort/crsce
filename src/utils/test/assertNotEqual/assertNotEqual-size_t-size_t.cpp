/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-size_t-size_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that lhs should not equal rhs
 * @param lhs size_t
 * @param rhs size_t
 * @param message std::string
 */
void Tester::assertNotEqual(const size_t lhs, const size_t rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
