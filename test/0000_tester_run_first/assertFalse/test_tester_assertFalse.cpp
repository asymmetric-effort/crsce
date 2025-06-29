/**
 * @file test_tester_assertFalse.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @brief Unit test for Tester::assertEqual, assertNotEqual, assertTrue, assertFalse.
 */


#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("tester_assertFalse");

    // assertFalse
    tester.assertFalse(false, "false should be false");

    tester.expectException<TestException>([&tester] {
        tester.assertFalse(true, "true should not be false");
    });

}
