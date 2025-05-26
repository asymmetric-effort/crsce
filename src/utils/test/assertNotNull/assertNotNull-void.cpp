/**
 * @file include/utils/test/assertNotNull/assertNotNull.h
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that ptr is not null
 * @param ptr Gpu::Ipc::Result
 * @param message std::string
 */
void Tester::assertNotNull(const void *ptr, const std::string &message) {
    if (ptr == nullptr)
        fail(std::format("Null pointer assertion failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}
