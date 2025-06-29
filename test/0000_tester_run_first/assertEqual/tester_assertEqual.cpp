/**
 * @file tester_assertEqual.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 * @brief Unit test for Tester::assertEqual
 */



#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

int main() {
    Tester tester("tester_assertEqual");

    tester.assertEqual(42, 42, "int equality");
    tester.assertEqual(1u, 1u, "unsigned equality");
    tester.assertEqual('a', 'a', "char equality");
    tester.assertEqual(3.14f, 3.14f, "float equality");
    tester.assertEqual(2.718, 2.718, "double equality");
    tester.assertEqual(1.00001f, 1.00002f, "float near-equal");
    tester.assertEqual(0.123456789, 0.123456788, "double near-equal");

    tester.pass();

    return tester.getFailCount()>0?1:EXIT_SUCCESS;
}
