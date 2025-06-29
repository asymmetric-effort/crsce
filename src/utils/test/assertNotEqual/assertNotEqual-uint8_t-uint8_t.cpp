/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-uint8_t-uint8_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief assert that a != b.
 * @param lhs uint8_t
 * @param rhs uint8_t
 * @param message std::string
 */
void Tester::assertNotEqual(const uint8_t lhs, const uint8_t rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
