/**
* @file src/utils/test/assertEqual/assertEqual-unsigned-int-unsigned-int.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a uint32_t
 * @param b uint32_t
 * @param message std::string&
 */
void Tester::assertEqual(uint32_t a, uint32_t b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}
