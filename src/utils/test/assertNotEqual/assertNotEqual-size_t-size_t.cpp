/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-size_t-size_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that a should equal b
 * @param a size_t
 * @param b size_t
 * @param message std::string
 */
void Tester::assertNotEqual(size_t a, size_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}
