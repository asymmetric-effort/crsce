/**
 * @file src/utils/test/assertEqual-size_t-size_t.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs size_t
 * @param rhs size_t
 * @param message std::string&
 */
void Tester::assertEqual(size_t lhs, size_t rhs, const std::string &message) {
    if (lhs == rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", lhs, rhs, message));
}
