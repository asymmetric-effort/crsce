// file: test/0200_cli/0210_compress/Compress-flag-block-size.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <map>
#include <string>
#include <format>
#include <vector>
#include <type_traits>
#include "utils/enum_ArgType.h"
#include "utils/struct_CliOptions.h"
#include "utils/test/Tester.h"
#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

/**
 * @brief Unit tests for the `--block-size` flag of the `compress` CLI.
 *
 * Verifies valid sizes (512, 1024, 2048, 4096) require an input file and show help,
 * and invalid sizes produce an error message.
 */

/**
 * @brief Entry point for block-size flag tests.
 *
 * Iterates bs from 511 to 4999, runs `compress --block-size <bs>`,
 * and asserts correct output behavior.
 *
 * @return EXIT_SUCCESS if all tests pass; EXIT_FAILURE on exception or assertion.
 */
int main() {
    Tester tester("test/0200_cli/0210_compress/Compress-flag-block-size.cpp");
    try {
        const std::map<int, bool> valid_sizes = {
            {512, true},
            {1024, true},
            {2048, true},
            {4096, true},
        };
        constexpr int max_blocks = 5000;
        for (int bs = 511; bs < max_blocks; ++bs) {
            if (bs % 100 == 0) {
                std::cout << " " << std::to_string(bs) << "/" << std::to_string(max_blocks) << " ";
            }else {
                std::cout << ".";
                std::cout.flush();
            }
            const bool is_valid = valid_sizes.contains(bs);
            const std::string expected = is_valid
                                             ? "Input file must be provided. Use -h for help\n"
                                             : "Error: --block-size is invalid";

            std::string command = std::string(target_binary) + " --block-size " + std::to_string(bs);
            const std::string output = utils::exec(command);

            // Split output and evaluate only the first line
            std::istringstream iss(output);
            std::string first_line;
            std::getline(iss, first_line);

            if (!expected.compare(first_line))
                throw std::invalid_argument(std::format(
                    "Unexpected response for block size. Expected '{}', got '{}'", expected, output));
            tester.pass();
        }
    } catch (const std::exception& e) {
        tester.fail(std::format("[ERROR] Exception occurred: {}", e.what()));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
