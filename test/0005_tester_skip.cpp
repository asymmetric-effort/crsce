// file: test/0005_tester_skip.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include <cstdlib>

int main() {
    Tester tester("0005_tester_skip.cpp", ThrowExceptionOnError);

    // This test should be skipped immediately.
    tester.skip("skipping this test as a placeholder");

    // The following assertions should never be reached.
    tester.fail("skip did not terminate the test");
    return EXIT_FAILURE;
}
