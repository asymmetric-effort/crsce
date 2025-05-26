/**
 * @file src/utils/test/assertFalse-bool.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name assertFalse
 * @brief assert that a condition is false
 * @param condition
 * @param message std::string&
 */
void Tester::assertFalse(const bool condition, const std::string& message) {
    if (!condition) {
        pass(std::format("ok: {}", message));
    }else{
        Tester::fail(std::format("assertFalse() failed: {}", message));
    }
}
