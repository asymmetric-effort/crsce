/**
 * @file include/utils/test/assertNotNull/assertNotNull-double.h
 * @brief Declares an assertion which expects non-null value.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that ptr is not null
 * @param ptr void*
 * @param message std::string
 */
void Tester::assertNotNull(const std::unique_ptr<double> &ptr, const std::string &message) {
    if (ptr == nullptr)
        fail(std::format("assertNotNull Failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}
