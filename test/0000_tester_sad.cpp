// file: test/0000_tester_happy.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include <exception>
#include <memory>
#include <string>

int main() {
    // Caveat: Test Tester, but don't trust tester in a test of tester

    Tester tester("test/0000_tester_sad", ThrowExceptionOnError);
    tester.expectException<TestException>([&]() {
        tester.assertTrue(false, "false should be false");
    });
    tester.expectException<TestException>([&]() {
        tester.assertTrue(1 + 1 == 3, "1+1 should not equal 3");
    });
    tester.expectException<TestException>([&]() {
        tester.assertNotNull(nullptr, "null should not be null");
    });
    tester.expectException<TestException>([&]() {
        std::shared_ptr<int> v;  // default-initialized, null
        tester.assertNotNull(v, "shared_ptr<int> should not be null");
    });
    tester.expectException<TestException>([&]() {
        std::shared_ptr<unsigned> v;  // default-initialized, null
        tester.assertNotNull(v, "shared_ptr<unsigned> should not be null");
    });
    tester.expectException<TestException>([&]() {
        std::shared_ptr<float> v;  // default-initialized, null
        tester.assertNotNull(v, "shared_ptr<float> should not be null");
    });
    tester.expectException<TestException>([&]() {
        std::shared_ptr<double> v;  // default-initialized, null
        tester.assertNotNull(v, "shared_ptr<double> should not be null");
    });
    tester.expectException<TestException>([&]() {
        std::weak_ptr<void> wp;
        tester.assertNotNull(wp, "weak_ptr locked should be null");
    });
    tester.expectException<TestException>([&]() {
        tester.assertEqual(0, 1, "0 should not equal 1");
    });
    tester.expectException<TestException>([&]() {
        tester.assertEqual(static_cast<unsigned int>(0), static_cast<unsigned int>(1), "0u should not equal 1u");
    });
    tester.expectException<TestException>([&]() {
        tester.assertEqual(static_cast<float>(0), static_cast<float>(1), "0u should not equal 1u");
    });
    tester.expectException<TestException>([&]() {
        tester.assertEqual('A', 'B', "'A' should not equal 'B'");
    });
    tester.expectException<TestException>([&]() {
        tester.assertEqual(2.718, 2.718, "2.718 should not equal 2.718");
    });
    return EXIT_SUCCESS;
}
