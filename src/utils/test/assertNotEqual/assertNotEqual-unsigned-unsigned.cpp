/**
 * @file src/utils/test/assertNotEqual/assertNotEqual-unsigned-unsigned.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that a should equal b
 * @param a unsigned int
 * @param b unsigned int
 * @param message std::string
 */
void Tester::assertNotEqual(unsigned int a, unsigned int b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}
