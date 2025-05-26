// file: test/0008_tester_misc_types.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include <cstdlib>

int main() {
    Tester tester("0008_tester_misc_types.cpp", ThrowExceptionOnError);

    // ---- unsigned int tests ----
    unsigned u1 = 100u;
    unsigned u2 = 200u;
    tester.assertEqual(u1, u1, "unsigned should be equal when same");
    tester.expectException<TestException>([&] { tester.assertEqual(u1, u2, "unsigned should not be equal"); });
    tester.assertNotEqual(u1, u2, "unsigned should not be equal when different");
    tester.expectException<TestException>([&] { tester.assertNotEqual(u1, u1, "unsigned should be equal"); });

    // ---- float tests ----
    float f1 = 3.14f;
    float f2 = 3.14f;
    float f3 = 2.718f;
    tester.assertEqual(f1, f2, "float should be equal when same");
    tester.expectException<TestException>([&] { tester.assertEqual(f1, f3, "float should not be equal"); });
    tester.assertNotEqual(f1, f3, "float should not be equal when different");
    tester.expectException<TestException>([&] { tester.assertNotEqual(f1, f2, "float should be equal"); });

    // ---- double tests ----
    double d1 = 6.626;
    double d2 = 6.626;
    double d3 = 9.81;
    tester.assertEqual(d1, d2, "double should be equal when same");
    tester.expectException<TestException>([&] { tester.assertEqual(d1, d3, "double should not be equal"); });
    tester.assertNotEqual(d1, d3, "double should not be equal when different");
    tester.expectException<TestException>([&] { tester.assertNotEqual(d1, d2, "double should be equal"); });

    // ---- char tests ----
    char c1 = 'a';
    char c2 = 'b';
    tester.assertNotEqual(c1, c2, "char should not be equal when different");
    tester.expectException<TestException>([&] { tester.assertNotEqual(c1, c1, "char should be equal"); });

    return EXIT_SUCCESS;
}
