/**
 * @file test/0100_generic/0110_utils/test_compress_flag_usage.cpp
 * @brief Verify `compress --help` outputs correct header, usage, and options
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "utils/exec.h"

constexpr auto target_binary = "build/bin/compress";

int main() {
    try {
        const std::string output = utils::exec("./build/bin/compress --help");
        const std::vector<std::string> expected={"",
            "(c) 2025 Asymmetric Effort, LLC.  All Rights Reserved.",
            "Usage: compress --in <inputfile> --out <outputfile>" ,
            "Options:" ,
            "  --in <inputfile>     specify input file (required)",
            "  --out <outputfile>   specify output file (required)",
            "  --help        Show this help message" ,
            "  --version     Show program version",
        };
        const std::vector<std::string> actual=output.split
        std::cout << output << std::endl;

        // // 1) Check copyright (two spaces after comma)
        // const std::string expectedCopyright =
        //     "(c) 2025 Asymmetric Effort, LLC.  All Rights Reserved.\n";
        // if (output.find(expectedCopyright) == std::string::npos) {
        //     std::cerr << "[FAIL] Missing or incorrect copyright.\n"
        //               << "       expected: '" << expectedCopyright << "'\n"
        //               << "         actual: '" << output << "'\n";
        //     return EXIT_FAILURE;
        // }
        //
        // // 2) Check usage line
        // const std::string expectedUsageStart =
        //     "Usage: compress --in <inputfile> --out <outputfile>\n";
        // if (output.find(expectedUsageStart) == std::string::npos) {
        //     std::cerr << "[FAIL] Usage text not found or incorrect.\n"
        //               << "       expected: '" << expectedUsageStart << "'\n"
        //               << "         actual: '" << output << "'\n";
        //     return EXIT_FAILURE;
        // }
        //
        // std::cout << "[PASS] `compress --help` output correct:\n" << output << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
