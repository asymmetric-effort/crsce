// file: test/0200_cli/0210_compress/Compress-flag-block-size.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <map>
#include <string>
#include <format>
#include "utils/struct_CliOptions.h"
#include "utils/test/Tester.h"
#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

void test_flag_block_size(Tester& tester) {
    try {
        const std::map<int, bool> valid_sizes = {
            {512, true},
            {1024, true},
            {2048, true},
            {4096, true},
        };
        constexpr int max_blocks = 5000;
        for (int bs = 511; bs < max_blocks; ++bs) {
            const bool is_valid = valid_sizes.contains(bs);
            if (bs % 100 == 0) {
                std::cout << " " << std::to_string(bs) << "/" << std::to_string(max_blocks) << " ";
            }else {
                std::cout << (is_valid?"+":".");
                std::cout.flush();
            }
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
                throw std::invalid_argument(
                    std::format("Unexpected response for block size. Expected '{}', got '{}'",
                        expected, output));
            tester.pass();
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        throw std::format("[ERROR] Exception occurred: {}", e.what());

    }
}

int main() {
    Tester tester("test/0200_cli/0210_compress/Compress-flag-block-size.cpp");
    try {
        test_flag_block_size(tester);
        return EXIT_SUCCESS;
    }catch (const std::exception& e) {
        tester.fail(e.what());
        return EXIT_FAILURE;
    }
}
