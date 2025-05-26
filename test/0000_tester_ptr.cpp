// file: test/0000_tester_ptr.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0000_tester_ptr.cpp
 * @brief Unit test for Tester::assertNotNull across raw, shared, unique, and weak pointers.
 *
 * Validates:
 *   - Null and non-null raw pointers.
 *   - Shared and unique pointer non-null checks.
 *   - Weak pointers lockable or not.
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

#include <memory>

int main() {
    Tester tester("0000_tester_ptr");

    // Raw pointer
    int val = 42;
    tester.assertNotNull(&val, "non-null raw pointer");
    tester.expectException<TestException>([&tester] {
        tester.assertNotNull(nullptr, "nullptr should throw");
    });

    // shared_ptr
    tester.assertNotNull(std::make_shared<int>(1), "shared_ptr<int>");
    tester.expectException<TestException>([&tester] {
        std::shared_ptr<int> p;
        tester.assertNotNull(p, "null shared_ptr should throw");
    });

    // unique_ptr
    tester.assertNotNull(std::make_unique<int>(1), "unique_ptr<int>");

    // shared_ptr typed overloads
    tester.assertNotNull(std::make_shared<unsigned>(1), "shared_ptr<unsigned>");
    tester.assertNotNull(std::make_shared<float>(1.1f), "shared_ptr<float>");
    tester.assertNotNull(std::make_shared<double>(3.14159), "shared_ptr<double>");
    tester.assertNotNull(std::make_shared<char>('x'), "shared_ptr<char>");

    // unique_ptr typed overloads
    tester.assertNotNull(std::make_unique<unsigned>(2), "unique_ptr<unsigned>");
    tester.assertNotNull(std::make_unique<float>(2.71f), "unique_ptr<float>");
    tester.assertNotNull(std::make_unique<double>(6.28), "unique_ptr<double>");

    // weak_ptr (locked should be non-null)
    tester.expectException<TestException>([&tester] {
        const std::weak_ptr<void> wp;
        tester.assertNotNull(wp, "null weak_ptr should throw");
    });

    const auto sp = std::make_shared<int>(99);
    const std::weak_ptr<int> wp = sp;
    tester.assertNotNull(wp, "non-null weak_ptr");

    tester.pass();
}
