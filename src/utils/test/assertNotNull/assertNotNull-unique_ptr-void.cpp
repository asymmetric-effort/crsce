/**
 * @file include/utils/test/assertNotNull/assertNotNull-void.h
 * @brief Declares an assertion which expects non-null value.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that ptr is not null
 * @param ptr std::unique_ptr<void>
 * @param message std::string
 */
void Tester::assertNotNull(const std::unique_ptr<void> &ptr, const std::string &message) {
    if (ptr == nullptr)
        fail(std::format("assertNotNull Failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}
