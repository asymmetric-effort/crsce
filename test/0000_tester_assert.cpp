// file: test/0000_tester_assert.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0000_tester_assert.cpp
 * @brief Unit test for Tester::assertEqual, assertNotEqual, assertTrue, assertFalse.
 *
 * This test verifies:
 *   - Integer, float, double, and char comparisons work.
 *   - Floating-point comparisons tolerate minimal precision drift.
 *   - True/false logic evaluates correctly.
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("0000_tester_assert");

    // assertTrue
    tester.assertTrue(true, "true should be true");
    tester.expectException<TestException>([] {
        Tester t("assertTrue fails", ThrowExceptionOnError);
        t.assertTrue(false, "false should not be true");
    });

    // assertFalse
    tester.assertFalse(false, "false should be false");
    tester.expectException<TestException>([] {
        Tester t("assertFalse fails", ThrowExceptionOnError);
        t.assertFalse(true, "true should not be false");
    });

    // assertEqual / assertNotEqual (int)
    tester.assertEqual(42, 42, "int equality");
    tester.assertNotEqual(1, 2, "int inequality");

    // unsigned
    tester.assertEqual(1u, 1u, "unsigned equality");
    tester.assertNotEqual(0u, 3u, "unsigned inequality");

    // char
    tester.assertEqual('a', 'a', "char equality");
    tester.assertNotEqual('a', 'b', "char inequality");

    // float (exact)
    tester.assertEqual(3.14f, 3.14f, "float equality");
    tester.assertNotEqual(3.14f, 3.15f, "float inequality");

    // float (fuzzy)
    tester.assertEqual(1.00001f, 1.00002f, "float near-equal");

    // double (exact)
    tester.assertEqual(2.718, 2.718, "double equality");
    tester.assertNotEqual(2.718, 3.14159, "double inequality");

    // double (fuzzy)
    tester.assertEqual(0.123456789, 0.123456788, "double near-equal");

    tester.pass();
}
