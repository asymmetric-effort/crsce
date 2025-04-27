// file: test/compress-flag-version.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

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

constexpr const char* target_binary = "build/bin/compress";

// Helper function to execute a command and capture stdout
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
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
        const std::string version = PROJECT_VERSION;
        if (version == "not_defined") {
            std::cout << "[FAIL] Cmake does not define PROJECT_VERSION. Got '"
                      << PROJECT_VERSION <<"'" << std::endl;
            return EXIT_FAILURE;
        }

        std::string expected = "CRSCE " PROJECT_NAME " " PROJECT_VERSION;
        std::string output = exec((std::string(target_binary) + " --version").c_str());

        if (output.find(expected) != std::string::npos) {
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
