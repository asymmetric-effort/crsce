/**
 * @file src/utils/test/assertNotEqual/assertNotEqual-unsigned-unsigned.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs unsigned int
 * @param rhs unsigned int
 * @param message std::string
 */
void Tester::assertNotEqual(const unsigned int lhs, const unsigned int rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
