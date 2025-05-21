// file: test/0010_ipc_communications_result_stream_operator.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Unit test for Gpu::Ipc::Result stream output operator.
 *
 * This test verifies that the overloaded `operator<<` correctly serializes
 * each Result enum value to its expected string representation. The test uses
 * an ostringstream to capture the output and compares it to known-good strings
 * for each enum constant.
 *
 * The Result values tested:
 * - Success
 * - Empty
 * - Blocked
 * - Shutdown
 * - Error
 */

#include "Gpu/Ipc/Result.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>

using Gpu::Ipc::Result;

int main() {
    int failures = 0;

    std::map<Result, std::string> expectedOutput = {
        {Result::Success,  "Success"},
        {Result::Empty,    "Empty"},
        {Result::Blocked,  "Blocked"},
        {Result::Shutdown, "Shutdown"},
        {Result::Error,    "Error"}
    };

    for (const auto& [value, expectedStr] : expectedOutput) {
        std::ostringstream oss;
        oss << value;

        if (oss.str() != expectedStr) {
            std::cerr << "[FAIL] operator<< for Result "
                      << static_cast<int>(value) << ": expected '"
                      << expectedStr << "', got '" << oss.str() << "'\n";
            ++failures;
        }
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Result stream operator test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failures.\n";
        return 1;
    }
}
