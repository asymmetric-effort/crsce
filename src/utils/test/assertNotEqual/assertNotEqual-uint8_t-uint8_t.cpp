/**
 * @file  src/utils/test/assertNotEqual/assertNotEqual-uint8_t-uint8_t.cpp
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief assert that a != b.
 * @param a uint8_t
 * @param b uint8_t
 * @param message std::string
 */
void Tester::assertNotEqual(uint8_t a, uint8_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}
