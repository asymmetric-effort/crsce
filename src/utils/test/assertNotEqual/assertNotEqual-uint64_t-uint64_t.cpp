/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-uint64_t-uint64_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

#if SIZE_MAX != UINT64_MAX
/**
 * @name assertNotEqual
 * @brief asserts that a should equal b
 * @param a uint64_t
 * @param b uint64_t
 * @param message std::string
 */
void Tester::assertNotEqual(uint64_t a, uint64_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}
#endif
