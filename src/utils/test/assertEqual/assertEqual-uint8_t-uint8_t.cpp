/**
 * @file src/utils/test/assertEqual/assertEqual-uint8_t-uint8_t.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs uint8_t
 * @param rhs uint8_t
 * @param message std::string&
 */
void Tester::assertEqual(uint8_t lhs, uint8_t rhs, const std::string& message) {
    if (lhs == rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", lhs, rhs, message));
}
