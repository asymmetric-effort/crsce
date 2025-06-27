/**
 * @file tester_buffer.cpp
 * @brief Verifies Gpu::Ipc::Result, Common::Buffer8, Common::Buffer64, and Gpu::Math::Matrix comparisons via Tester assertions.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include "Common/Buffer8.h"
#include "Common/Buffer64.h"
#include <cstdlib>

int main() {
    Tester tester("tester_buffer.cpp",ThrowExceptionOnError);

    // ---- Buffer8 tests ----
    using Common::Buffer8;
    const Buffer8 buf1 = {1, 2, 3};
    const Buffer8 buf2 = {1, 2, 3};
    const Buffer8 buf3 = {1, 2, 4};
    tester.assertEqual(buf1, buf2, "Buffer8 contents should be equal");
    tester.expectException<TestException>([&] {
        tester.assertEqual(buf1, buf3, "Buffer8 contents should be equal");
    });
    tester.assertNotEqual(buf1, buf3, "Buffer8 contents should not be equal (1)");
    tester.expectException<TestException>([&] {
        tester.assertNotEqual(buf1, buf2, "Buffer8 contents should not be equal (2)");
    });

    // ---- Buffer64 tests ----
    using Common::Buffer64;
    const Buffer64 b641 = {1ULL, 2ULL, 3ULL};
    const Buffer64 b642 = {1ULL, 2ULL, 3ULL};
    const Buffer64 b643 = {1ULL, 2ULL, 4ULL};

    tester.assertEqual(b641, b642, "Buffer64 contents should be equal");
    tester.expectException<TestException>(
        [&] { tester.assertEqual(b641, b643, "Buffer64 contents should be equal"); }
    );
    tester.assertNotEqual(b641, b643, "Buffer64 contents should not be equal (1)");
    tester.expectException<TestException>(
        [&] { tester.assertNotEqual(b641, b642, "Buffer64 contents should not be equal (1)"); }
    );

    return tester.getFailCount()>0?1:EXIT_SUCCESS;
}
