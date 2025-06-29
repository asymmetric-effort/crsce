/**
* @file src/utils/test/assertEqual-string-string.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs std::string
 * @param rhs std::string
 * @param message std::string
 */
void Tester::assertEqual(const std::string& lhs, const std::string& rhs, const std::string& message) {
    if (lhs == rhs) {
        pass(std::format("ok: {}", message));
    }
    else {
        fail(std::format("assertEqual failed({} != {}): {}", lhs, rhs, message));
    }
}
