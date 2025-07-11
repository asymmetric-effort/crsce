/**
* @file src/utils/test/assertEqual/assertEqual-unsigned-int-unsigned-int.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs uint32_t
 * @param rhs uint32_t
 * @param message std::string&
 */
void Tester::assertEqual(uint32_t lhs, uint32_t rhs, const std::string& message) {
    if (lhs == rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", lhs, rhs, message));
}
