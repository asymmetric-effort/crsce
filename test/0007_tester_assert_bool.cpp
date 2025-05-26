// file: test/0007_tester_assert_bool.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include <cstdlib>

int main() {
    Tester tester("0007_tester_assert_bool.cpp", ThrowExceptionOnError);

    // ---- assertTrue tests ----
    tester.assertTrue(true, "assertTrue should pass on true");
    tester.expectException<TestException>([&] {
        tester.assertTrue(false, "assertTrue should fail on false");
    });

    // ---- assertFalse tests ----
    tester.assertFalse(false, "assertFalse should pass on false");
    tester.expectException<TestException>([&] {
        tester.assertFalse(true, "assertFalse should fail on true");
    });

    return EXIT_SUCCESS;
}
