/**
 * @file src/utils/test/assertEqual/assertEqual-Gpu::Ipc::Result-Gpu::Ipc::Result.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"
#include "utils/to_underlying.h"


/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a Gpu::Ipc::Result
 * @param b Gpu::Ipc::Result
 * @param message std::string&
 */
void Tester::assertEqual(const Gpu::Ipc::Result a, const Gpu::Ipc::Result b, const std::string &message) {
    assertEqual(std::to_underlying(a), std::to_underlying(b), message);
}
