/**
 * @file include/utils/test/assertNotNull/assertNotNull-Gpu-Ipc-Result.h
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotEqual
 * @brief asserts that a should equal b
 * @param a int
 * @param b int
 * @param message std::string
 */

void Tester::assertNotEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string &message) {
  assertNotEqual(static_cast<uint8_t>(a), static_cast<uint8_t>(b), message);
}
