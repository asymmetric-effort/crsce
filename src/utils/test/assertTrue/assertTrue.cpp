/**
 * @file src/utils/test/assertTrue.cpp
 * @brief Declare a tester assertion which asserts a true condition.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertTrue
 * @brief assert that the input condition must be true
 * @param condition bool
 * @param message std::string
 */
void Tester::assertTrue(const bool condition, const std::string& message) {
    if (condition) {
        pass(std::format("ok: {}", message));
    }else{
        fail(std::format("assertTrue Failed: {}", message));
    }
}
