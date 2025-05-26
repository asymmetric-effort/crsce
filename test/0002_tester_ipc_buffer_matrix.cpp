// file: test/0002_tester_ipc_buffer_matrix.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include "Gpu/Ipc/Result.h"
#include "Gpu/Common/Buffer8.h"
#include "Gpu/Common/Buffer64.h"
#include "Gpu/Math/Matrix.h"
#include <cstdlib>

int main() {
    Tester tester("0002_tester_ipc_buffer_matrix.cpp");

    // ---- Result tests ----
    using Gpu::Ipc::Result;
    constexpr auto r1 = Result::Success;
    constexpr auto r2 = Result::Closed;
    tester.assertEqual(r1, r1, "Result values should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(r1, r2, "Result values should be equal"); });
    tester.assertNotEqual(r1, r2, "Result values should not be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(r1, r1, "Result values should not be equal"); });

    // ---- Buffer8 tests ----
    using Common::Buffer8;
    Buffer8 buf1 = {1, 2, 3};
    Buffer8 buf2 = {1, 2, 3};
    Buffer8 buf3 = {1, 2, 4};
    tester.assertEqual(buf1, buf2, "Buffer8 contents should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(buf1, buf3, "Buffer8 contents should be equal"); });
    tester.assertNotEqual(buf1, buf3, "Buffer8 contents should not be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(buf1, buf2, "Buffer8 contents should not be equal"); });

    // ---- Buffer64 tests ----
    using Common::Buffer64;
    Buffer64 b641 = {1ULL, 2ULL, 3ULL};
    Buffer64 b642 = {1ULL, 2ULL, 3ULL};
    Buffer64 b643 = {1ULL, 2ULL, 4ULL};
    tester.assertEqual(b641, b642, "Buffer64 contents should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(b641, b643, "Buffer64 contents should be equal"); });
    tester.assertNotEqual(b641, b643, "Buffer64 contents should not be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(b641, b642, "Buffer64 contents should not be equal"); });

    // ---- Matrix tests ----
    using Gpu::Math::Matrix;
    Matrix m1(2, 2);
    m1.at(0, 0) = 1.0; m1.at(0, 1) = 2.0;
    m1.at(1, 0) = 3.0; m1.at(1, 1) = 4.0;
    Matrix m2(2, 2);
    m2.at(0, 0) = 1.0; m2.at(0, 1) = 2.0;
    m2.at(1, 0) = 3.0; m2.at(1, 1) = 4.0;
    Matrix m3(2, 2);
    m3.at(0, 0) = 1.0; m3.at(0, 1) = 2.0;
    m3.at(1, 0) = 3.0; m3.at(1, 1) = 0.0;
    tester.assertEqual(m1, m2, "Matrix contents should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(m1, m3, "Matrix contents should be equal"); });
    tester.assertNotEqual(m1, m3, "Matrix contents should not be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(m1, m2, "Matrix contents should not be equal"); });

    return EXIT_SUCCESS;
}
