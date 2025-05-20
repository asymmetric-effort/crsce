// file: test/0000_tester_happy.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include <memory>
#include <string>

int main() {
    // Caveat: Test Tester, but don't trust tester in a test of tester

    Tester tester("test/0000_tester_happy", TerminateOnError);

    // assertTrue
    tester.assertTrue(true, "true should be true");
    tester.assertTrue(1 + 1 == 2, "1+1 should equal 2");

    //tester.assertNull(nullptr, "null should be null");

    // assertNotNull raw pointer
    int x = 42;
    tester.assertNotNull(&x, "Raw pointer &x should not be null");
    std::cerr << "tester.assertNotNull() handles true ok" << std::endl;

    // assertNotNull shared_ptr<int>
    auto sp_int = std::make_shared<int>(7);
    tester.assertNotNull(sp_int, "shared_ptr<int> should not be null");

    // assertNotNull shared_ptr<unsigned>
    auto sp_uint = std::make_shared<unsigned>(7u);
    tester.assertNotNull(sp_uint, "shared_ptr<unsigned> should not be null");

    // assertNotNull shared_ptr<float>
    auto sp_float = std::make_shared<float>(7.0f);
    tester.assertNotNull(sp_float, "shared_ptr<float> should not be null");

    // assertNotNull shared_ptr<double>
    auto sp_double = std::make_shared<double>(7.1);
    tester.assertNotNull(sp_double, "shared_ptr<double> should not be null");

    // assertNotNull weak_ptr locked
    std::weak_ptr<void> wp = std::static_pointer_cast<void>(sp_double);
    tester.assertNotNull(wp, "weak_ptr locked should not be null");

    // assertEqual int
    tester.assertEqual(10, 10, "10 should equal 10");
    // assertEqual unsigned int
    tester.assertEqual(static_cast<unsigned int>(5), static_cast<unsigned int>(5), "5u should equal 5u");
    // assertEqual char
    tester.assertEqual('A', 'A', "'A' should equal 'A'");
    // assertEqual float
    tester.assertEqual(3.14f, 3.14f, "3.14f should equal 3.14f");
    // assertEqual double
    tester.assertEqual(2.718, 2.718, "2.718 should equal 2.718");
}
