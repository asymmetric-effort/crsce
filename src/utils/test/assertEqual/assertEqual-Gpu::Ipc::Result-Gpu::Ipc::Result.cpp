/**
 * @file src/utils/test/assertEqual/assertEqual-Gpu::Ipc::Result-Gpu::Ipc::Result.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"


/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a Gpu::Ipc::Result
 * @param b Gpu::Ipc::Result
 * @param message std::string&
 */
void Tester::assertEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string& message) {
    assertEqual(static_cast<uint8_t>(a), static_cast<uint8_t>(b), message);
}
