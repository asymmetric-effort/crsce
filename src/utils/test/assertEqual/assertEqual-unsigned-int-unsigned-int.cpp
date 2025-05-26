/**
* @file src/utils/test/assertEqual/assertEqual-unsigned-int-unsigned-int.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a unsigned int
 * @param b unsigned int
 * @param message std::string&
 */
void Tester::assertEqual(unsigned int a, unsigned int b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}
