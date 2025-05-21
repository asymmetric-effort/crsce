// file: test/0010_ipc_communications_result.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Unit test for Gpu::Ipc::Result to-string conversion.
 *
 * This test validates the behavior of `resultToString(Result)` for each
 * enumerated value in the Gpu::Ipc::Result enum. The function is expected
 * to return a stable and correct human-readable string for each Result value.
 *
 * The test checks:
 * - Success
 * - Empty
 * - Blocked
 * - Shutdown
 * - Error
 *
 * Failures are logged to stderr with both expected and actual output.
 * A summary result is printed to stdout.
 */

#include "Gpu/Ipc/Result.h"
#include <iostream>
#include <string>

using Gpu::Ipc::Result;

int main() {
    int failures = 0;

    auto test = [&](Result r, const std::string& expected) {
        std::string actual = resultToString(r);
        if (actual != expected) {
            std::cerr << "[FAIL] Result " << static_cast<int>(r)
                      << ": expected '" << expected
                      << "', got '" << actual << "'\n";
            ++failures;
        }
    };

    test(Result::Success,  "Success");
    test(Result::Empty,    "Empty");
    test(Result::Blocked,  "Blocked");
    test(Result::Shutdown, "Shutdown");
    test(Result::Error,    "Error");

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Result enum test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failures.\n";
        return 1;
    }
}
