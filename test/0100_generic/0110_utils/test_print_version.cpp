/**
* @file test/0100_generic/0110_utils/test_print_version.cpp
 * @brief Unit test for utils::print_version() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/print_version.h"
#include "utils/test/Tester.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <regex>

int main() {
    Tester tester("utils::print_version");

    // Capture stdout
    std::ostringstream captured;
    auto* old_buf = std::cout.rdbuf(captured.rdbuf());

    // Invoke
    utils::print_version();

    // Restore stdout
    std::cout.rdbuf(old_buf);

    const std::string output = captured.str();

    // The version output should be non-empty and contain something like "v" or a digit
    tester.assertTrue(!output.empty(), "print_version should produce output");
    std::regex version_pattern(R"(\d+\.\d+\.\d+)");  // e.g. "1.2.3"
    tester.assertTrue(
        std::regex_search(output, version_pattern),
        "print_version output should contain semantic version"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
