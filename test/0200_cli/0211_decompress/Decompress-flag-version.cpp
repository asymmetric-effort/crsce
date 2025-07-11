/**
 * @file test/0200_cli/0211_decompress/Decompress-flag-version.cpp
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

#ifndef PROJECT_VERSION
#define PROJECT_VERSION "not_defined"
#endif

constexpr auto target_binary = "build/bin/compress";

int main() {
    Tester tester("test/0200_cli/0211_decompress/Decompress-flag-version.cpp");
    try {

        const std::string project_name = PROJECT_NAME;
        const std::string project_version = PROJECT_VERSION;

        if (project_version == "not_defined") {
            std::cout << "[FAIL] Cmake does not define PROJECT_VERSION. Got '"
                      << PROJECT_VERSION <<"'" << std::endl;
            return EXIT_FAILURE;
        }

        const std::string expected = "CRSCE " + project_name + " " + project_version;

        if (const std::string output = utils::exec((std::string(target_binary) + " --version").c_str()); output.find(expected) != std::string::npos) {
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
