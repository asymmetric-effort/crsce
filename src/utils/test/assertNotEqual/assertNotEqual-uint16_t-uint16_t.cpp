/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-uint16_t-uint16_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs uint16_t
 * @param rhs uint16_t
 * @param message std::string
 */
void Tester::assertNotEqual(const uint16_t lhs, const uint16_t rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
