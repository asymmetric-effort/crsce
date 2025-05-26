/**
 * @file include/utils/test/assertNotNull/assertNotNull-float.h
 * @brief Declares an assertion which expects non-null value.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that ptr is not null
 * @param ptr std::shared_ptr<float>
 * @param message std::string
 */
void Tester::assertNotNull(const std::shared_ptr<float> &ptr, const std::string &message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}
