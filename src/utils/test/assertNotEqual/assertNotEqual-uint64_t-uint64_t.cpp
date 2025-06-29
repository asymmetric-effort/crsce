/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-uint64_t-uint64_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

#if SIZE_MAX != UINT64_MAX
/**
 * @name assertNotEqual
 * @brief asserts that lhs should equal rhs
 * @param lhs uint64_t
 * @param rhs uint64_t
 * @param message std::string
 */
void Tester::assertNotEqual(const uint64_t lhs, const uint64_t rhs, const std::string& message) {
    if (lhs != rhs)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", lhs, rhs, message));
}
#endif
