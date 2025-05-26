/**
 * @file src/utils/test/assertEqual-int-int.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a int
 * @param b int
 * @param message std::string&
 */
void Tester::assertEqual(int a, int b, const std::string &message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}
