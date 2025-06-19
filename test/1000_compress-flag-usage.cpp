/**
 * @file 1000_compress-flag-usage.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>

#ifndef COPYRIGHT
#define COPYRIGHT "not_defined"
#endif

constexpr auto target_binary = "build/bin/compress";

// Helper function to execute a command and capture stdout
std::string exec(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (!feof(pipe.get())) {
        // read up to buffer.size() bytes
        if (const size_t n = fread(buffer.data(), 1, buffer.size(), pipe.get()); n > 0) {
            // explicitly copy exactly n bytes
            result.append(buffer.data(), n);
        }
    }
    return result;
}

int main() {
    try {
        const std::string expectedCopyright = std::string(COPYRIGHT) + "\n";
        const std::string expectedUsageStart = "Usage: "+std::string(target_binary)+" --in <inputfile> --out <outputfile>\n";

        const std::string output = exec(target_binary);

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
