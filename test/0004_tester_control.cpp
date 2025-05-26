// file: test/0004_tester_control.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
/**
 * @file 0004_tester_control.cpp
 * @brief Exercises Tester::pass, Tester::fail, Tester::recoverFail and Tester::debug, and validates the internal pass/fail/skip counters.
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include <cstdlib>

int main() {
    Tester tester("0004_tester_control.cpp",ThrowExceptionOnError);

    // ---- Record passes and fails ----
    tester.pass("first pass");
    tester.assertEqual(tester.getPassCount(), 1, "after first pass: pass count should be 1");
    tester.assertEqual(tester.getFailCount(), 0, "after first pass: fail count should be 0");
    tester.assertEqual(tester.getSkipCount(), 0, "after first pass: skip count should be 0");

    tester.pass();
    tester.assertEqual(tester.getPassCount(), 5, "after second pass: pass count should be 5");
    tester.assertEqual(tester.getFailCount(), 0, "after second pass: fail count should remain 0");

    tester.expectException<TestException>([&tester] {
        tester.fail("first fail");
    });
    tester.assertEqual(tester.getPassCount(), 8, "after first fail: pass count should be 8");
    tester.assertEqual(tester.getFailCount(), 0, "after first fail: fail count should be 0");

    tester.expectException<TestException>([&tester] {
        tester.fail();
    });
    tester.assertEqual(tester.getFailCount(), 0, "after second fail: fail count should be 0");

    // recover failures
    tester.recoverFail();
    tester.assertEqual(tester.getFailCount(), 0, "after recoverFail: fail count should be 0");
    tester.recoverFail();
    tester.assertEqual(tester.getFailCount(), 0, "after recoverFail twice: fail count should be 0");

    // ---- Debug should not affect counts ----
    tester.debug("debug message");
    tester.assertEqual(tester.getPassCount(), 14, "after debug: pass count should remain 14");
    tester.assertEqual(tester.getFailCount(), 0, "after debug: fail count should remain 0");
    tester.assertEqual(tester.getSkipCount(), 0, "after debug: skip count should remain 0");

    return tester.getFailCount()>0?1:EXIT_SUCCESS;
}
