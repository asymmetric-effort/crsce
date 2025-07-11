/**
 * @file test_tester_size_uint.cpp
 * @brief Verifies size_t and uint8_t/uint16_t/uint64_t overloads in Tester::assertEqual/assertNotEqual.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include <cstdint>
#include <cstddef>

int main() {
    Tester tester("0001_tester_size_uint.cpp", ThrowExceptionOnError);

    // ---- size_t tests ----
    constexpr size_t s1 = 42;
    constexpr size_t s2 = 7;
    tester.assertEqual(s1, s1, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(s1, s2, "operands should be equal"); });
    tester.assertNotEqual(s1, s2, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(s1, s1, "operands should be equal"); });

    // ---- uint8_t tests ----
    constexpr uint8_t u8_1 = 0xAB;
    constexpr uint8_t u8_2 = 0xCD;
    tester.assertEqual(u8_1, u8_1, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(u8_1, u8_2, "operands should be equal"); });
    tester.assertNotEqual(u8_1, u8_2, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(u8_1, u8_1, "operands should be equal"); });

    // ---- uint16_t tests ----
    constexpr uint16_t u16_1 = 0x1234;
    constexpr uint16_t u16_2 = 0x5678;
    tester.assertEqual(u16_1, u16_1, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(u16_1, u16_2, "operands should be equal"); });
    tester.assertNotEqual(u16_1, u16_2, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(u16_1, u16_1, "operands should be equal"); });

#if SIZE_MAX != UINT64_MAX
    // ---- uint64_t tests ----
    constexpr uint64_t u64_1 = 0x12345678ABCDEF00ULL;
    constexpr uint64_t u64_2 = 0x00FEDCBA87654321ULL;

    tester.assertEqual(u64_1, u64_1, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertEqual(u64_1, u64_2, "operands should be equal"); });
    tester.assertNotEqual(u64_1, u64_2, "operands should be equal");
    tester.expectException<TestException>([&] { tester.assertNotEqual(u64_1, u64_1, "operands should be equal"); });
#endif

    return tester.getFailCount() > 0 ? 1 : EXIT_SUCCESS;
}
