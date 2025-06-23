/**
 * @file 1000_compress-flag-version.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>

#ifndef PROJECT_VERSION
#define PROJECT_VERSION "not_defined"
#endif

constexpr auto target_binary = "build/bin/compress";

// Helper function to execute a command and capture stdout
std::string exec(const char* cmd) {
    // heap or stack—doesn't matter here, but vector is fine too
    std::array<char, 128> buffer;
    std::string result;
    result.reserve(1024);

    const auto pipe = std::unique_ptr<FILE, decltype(&pclose)>{ popen(cmd, "r"), pclose };
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
        const std::string project_name = PROJECT_NAME;
        const std::string project_version = PROJECT_VERSION;
        if (project_version == "not_defined") {
            std::cout << "[FAIL] Cmake does not define PROJECT_VERSION. Got '"
                      << PROJECT_VERSION <<"'" << std::endl;
            return EXIT_FAILURE;
        }

        const std::string expected = "CRSCE " + project_name + " " + project_version;

        if (const std::string output = exec((std::string(target_binary) + " --version").c_str()); output.find(expected) != std::string::npos) {
            std::cout << "[PASS] --version output correct: " << output;
            return EXIT_SUCCESS;
        } else {
            std::cerr << "[FAIL] Expected '" << expected << "' but got: " << output;
            return EXIT_FAILURE;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
