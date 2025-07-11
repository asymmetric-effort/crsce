/**
 * @file test/0200_cli/0210_compress/Compress-flag-usage.cpp
 * @brief Unit tests for utils::Option struct and CliOptions alias
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/enum_ArgType.h"
#include "utils/struct_CliOptions.h"
#include "utils/test/Tester.h"
#include <type_traits>
#include <vector>
#include <string>
#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

void test_compress_with_no_args(Tester& tester) {
    try {
        const std::string output = utils::exec(target_binary);
        throw std::invalid_argument(output);
    } catch (std::invalid_argument& _) {
        tester.pass();
    }
}

void evaluate_usage_result(const std::string& output) {

    const std::string expectedCopyright = std::string(COPYRIGHT) + "\n";
    const std::string expectedUsageStart = "Usage: " + std::string(target_binary) +
        " --in <inputfile> --out <outputfile>\n";

    if (output.find(expectedCopyright) == std::string::npos) {
        throw "[FAIL] Missing or incorrect copyright.\n";
    }
    if (output.find(expectedUsageStart) == std::string::npos) {
        throw "[FAIL] Usage text not found or incorrect.\n";
    }
    std::cout << "[PASS] help/usage output is correct" << std::endl;
}

void test_compress_with_short_help_flag(Tester& tester) {
    const std::string output = utils::exec(std::string(target_binary) + "-h");
    evaluate_usage_result(output);
}

void test_compress_with_long_help_flag(Tester& tester) {
    const std::string output = utils::exec(std::string(target_binary) + "--help");
    evaluate_usage_result(output);
}

int main() {
    Tester tester("test/0200_cli/0210_decompress/Compress-flag-version.cpp");
    try {
        test_compress_with_no_args(tester);
        test_compress_with_short_help_flag(tester);
        test_compress_with_long_help_flag(tester);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
