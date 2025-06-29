/**
* @file test_tester_assertNotEqual_happy.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @brief Unit test for Tester::assertNotEqual
 */


#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("tester_assertNotEqual");

    tester.expectException<TestException>([&tester]() {
        tester.assertNotEqual(1, 2, "int inequality");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertNotEqual(0u, 3u, "unsigned inequality");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertNotEqual('a', 'b', "char inequality");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertNotEqual(3.14f, 3.15f, "float inequality");
    });

    tester.expectException<TestException>([&tester]() {
        tester.assertNotEqual(2.718, 3.14159, "double inequality");
    });

    tester.pass();

    return tester.getFailCount() > 0 ? 1 : EXIT_SUCCESS;
}
