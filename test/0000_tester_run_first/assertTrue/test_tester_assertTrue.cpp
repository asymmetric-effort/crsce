/**
 * @file test_tester_assertTrue.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @brief Unit test for Tester::assertEqual, assertNotEqual, assertTrue, assertFalse.
 */


#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("tester_assertTrue");

    // assertTrue
    tester.assertTrue(true, "true should be true");

    tester.expectException<TestException>([&tester] {
        tester.assertTrue(false, "false should not be true");
    });

}
