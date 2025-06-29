/**
 * @file test_tester_skip.cpp
 * @brief Verifies that Tester::skip terminates the test immediately without executing further assertions.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include <cstdlib>

int main() {
    Tester tester("tester_skip.cpp", ThrowExceptionOnError);

    // This test should be skipped immediately.
    tester.skip("skipping this test as a placeholder");

    // The following assertions should never be reached.
    tester.fail("skip did not terminate the test");
    return EXIT_FAILURE;
}
