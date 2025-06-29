/**
* @file test_tester_assertEqual_sad.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @brief Unit test for Tester::assertEqual
 */


#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("test_tester_assertEqual_sad");

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            42,
            0,
            "int equality (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            1u,
            0u,
            "unsigned equality (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            'a',
            'b',
            "char equality (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            3.14f,
            3.01f,
            "float equality (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            2.718,
            2.008,
            "double equality (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            1.00001f,
            1.00010f,
            "float near-equal (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            0.123456789,
            0.123456888,
            "double near-equal (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            "foo_literal",
            "bar_literal",
            "string lhs should equal rhs (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            std::string("foo"),
            std::string("bar"),
            "string lhs should equal rhs (expect failure)");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertEqual(
            'a',
            'b',
            "string lhs should equal rhs (expect failure)");
    });

    return tester.getFailCount() > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
