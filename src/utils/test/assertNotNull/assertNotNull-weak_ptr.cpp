/**
 * @file include/utils/test/assertNotNull/assertNotNull.h
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief asserts that lhs should equal rhs
 * @param ptr std::weak_ptr<void>
 * @param message std::string
 */
void Tester::assertNotNull(const std::weak_ptr<void> &ptr, const std::string &message) {
    if (auto sp = ptr.lock()) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] Null weak_ptr assertion failed: " << message << std::endl;
        fail();
    }
}
