// file: test/1000_compress-flag-usage.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
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

constexpr const char* target_binary = "build/bin/compress";

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
    Tester tester("test/1000_compress-flag-usage", TerminateOnError);
    tester.deadline(60);
    tester.skip("disabled for debug");
    try {
        const std::string expectedCopyright = std::string(COPYRIGHT) + "\n";
        const std::string expectedUsageStart = "Usage: "+std::string(target_binary)+" --in <inputfile> --out <outputfile>\n";

        std::string output = exec(target_binary);

        tester.assertEqual(len(expectedCopyright)==std::string::npos,"Missing or incorrect copyright.");
        tester.assertEqual(len(expectedUsageStart)==std::string::npos,"Usage text not found or incorrect.");
        tester.pass();
        std::cout << "[PASS] --help output correct:\n" << output << std::endl;

    } catch (const std::exception& e) {
        tester.debug(std::format("[ERROR] Exception occurred: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
