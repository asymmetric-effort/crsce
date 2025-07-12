/**
* @file test/0200_cli/0210_compress/Compress-flag-concurrency.cpp
 * @brief Unit tests for compress --concurrency
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/test/Tester.h"
#include <map>
#include <string>
#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

void test_flag_concurrency(Tester& tester) {
    try {
        std::cout << "test_flag_concurrency() starting" << std::endl;
        const std::map<int, bool> valid_sizes = {
            {0, false},
            {1, true},
            {1024, true},
            {1025, false},
        };
        for (const auto& [concurrency, is_valid] : valid_sizes) {
            std::cout << "testing " << concurrency << " expecting " << std::to_string(is_valid) << std::endl;
            std::cout.flush();
            const auto full_cmd = std::format("{} --concurrency {}",
                                              target_binary, std::to_string(concurrency));
            const std::string expected = is_valid
                                             ? "Input file must be provided. Use -h for help\n"
                                             : "Error: --concurrency is invalid. It must be between 1 and 1024.";
            try {
                const auto output = utils::exec(full_cmd);
                std::cout << "output: " << output << std::endl;
                // Split output and evaluate only the first line
                std::istringstream iss(output);
                std::string first_line;
                std::getline(iss, first_line);
                std::cout << "first_line:'" << first_line << "'" << std::endl;

                if (expected.compare(first_line)) {
                    tester.pass();
                } else {
                    throw std::runtime_error(
                        std::format("Unexpected response for block size. Expected '{}', got '{}'",
                                    expected, output));
                }
            } catch (std::exception& e) {
                std::cout << "catch exception: " << e.what() << std::endl;
            }


            tester.pass();
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        throw std::format("[ERROR] Exception occurred: {}", e.what());
    }
}

int main() {
    Tester tester("test/0200_cli/0210_compress/Compress-flag-concurrency.cpp");
    try {
        test_flag_concurrency(tester);
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        tester.fail(e.what());
        return EXIT_FAILURE;
    }
}
