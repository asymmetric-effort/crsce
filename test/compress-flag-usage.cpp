// file: test/compress-flag-usage.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

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

// Helper function to execute a command and capture stdout
std::string exec(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    try {
        const std::string expectedCopyright = std::string(COPYRIGHT) + "\n";
        const std::string expectedUsageStart = "Usage: ./build/compress --in <inputfile> --out <outputfile>\n";

        std::string output = exec("./build/compress");

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
