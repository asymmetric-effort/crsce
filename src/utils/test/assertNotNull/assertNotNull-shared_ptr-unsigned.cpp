/**
 * @file include/utils/test/assertNotNull/assertNotNull-unsigned.h
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that ptr is not null
 * @param ptr std::shared_ptr<unsigned>
 * @param message std::string
 */
void Tester::assertNotNull(const std::shared_ptr<unsigned> &ptr, const std::string &message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}
