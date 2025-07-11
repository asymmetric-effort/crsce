/**
 * @file test/0200_cli/0211_decompress/Decompress-flag-usage.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>
#include "utils/exec.h"
#include "utils/test/Tester.h"

#ifndef COPYRIGHT
#define COPYRIGHT "not_defined"
#endif

constexpr auto target_binary = "build/bin/compress";

int main() {
    Tester tester("test/0200_cli/0210_decompress/Compress-flag-version.cpp");
    try {
        const std::string expectedCopyright = std::string(COPYRIGHT) + "\n";
        const std::string expectedUsageStart = "Usage: "+std::string(target_binary)+" --in <inputfile> --out <outputfile>\n";

        const std::string output = utils::exec(target_binary);

        if (output.find(expectedCopyright) == std::string::npos) {
            std::cerr << "[FAIL] Missing or incorrect copyright.\n";
            return EXIT_FAILURE;
        }

        if (output.find(expectedUsageStart) == std::string::npos) {
            std::cerr << "[FAIL] Usage text not found or incorrect.\n";
            return EXIT_FAILURE;
        }

        std::cout << "[PASS] --help output correct:\n" << output << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
