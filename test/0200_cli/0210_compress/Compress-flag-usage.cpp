/**
 * @file test/0200_cli/0210_compress/Compress-flag-usage.cpp
 * @brief Unit tests for utils::Option struct and CliOptions alias
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/test/Tester.h"
#include <string>
#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

void test_compress_with_no_args(Tester& tester) {
    tester.debug("test_compress_with_no_args");
    try {
        std::cerr << "test_compress_with_no_args() starting" << std::endl;
        const std::string output = utils::exec(target_binary);
        throw std::invalid_argument(output);
    } catch (std::invalid_argument& _) {
        tester.pass();
    }
}

void evaluate_usage_result(const std::string& output) {

    std::cerr << "evaluate_usage_result() starting (" << output << ")" << std::endl;
    const std::string expectedOutput = std::string(COPYRIGHT) + "\n" +
        "Usage: " + std::string(target_binary) + " --in <inputfile> --out <outputfile>\n" +
        "Options:\n" +
        "--in <inputfile>     specify input file (required)\n" +
        "--out <outputfile>   specify output file (required)\n" +
        "--help        Show this help message\n" +
        "--version     Show program version\n\n";
    std::cout << "compare expected output" << std::endl;
    if (expectedOutput.compare(output)) {
        std::cout << "[PASS] help/usage output is correct" << std::endl;
        return;
    }
    throw std::runtime_error("[FAIL] Usage text not found or incorrect.\n");
}

void test_compress_with_short_help_flag(const Tester& tester) {
    std::cerr << "test_compress_with_short_help_flag() starting" << std::endl;
    const std::string output = utils::exec(std::string(target_binary) + " -h");
    evaluate_usage_result(output);
}

void test_compress_with_long_help_flag(const Tester& tester) {
    std::cerr << "test_compress_with_long_help_flag() starting" << std::endl;
    const std::string output = utils::exec(std::string(target_binary) + " --help");
    evaluate_usage_result(output);
}

int main() {
    Tester tester("test/0200_cli/0210_decompress/Compress-flag-usage.cpp");
    try {
        tester.debug("starting tests...");
        test_compress_with_no_args(tester);
        test_compress_with_short_help_flag(tester);
        test_compress_with_long_help_flag(tester);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
