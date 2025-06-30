/**
* @file test/0100_generic/0110_utils/test_print_usage.cpp
 * @brief Unit test for utils::print_usage() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/print_usage.h"
#include "utils/test/Tester.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

int main() {
    Tester tester("utils::print_usage");

    // Capture stdout
    const std::ostringstream captured;
    auto* old_buf = std::cout.rdbuf(captured.rdbuf());

    // Invoke with a known program name
    const auto prog = "myprog";
    utils::print_usage(prog);

    // Restore stdout
    std::cout.rdbuf(old_buf);

    const std::string output = captured.str();

    // Expect at least one line containing "Usage: myprog"
    tester.assertTrue(
        output.find(std::string("Usage: ") + prog) != std::string::npos,
        "print_usage should include 'Usage: myprog'"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
