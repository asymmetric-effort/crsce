/**
 * @file test/0200_cli/0210_decompress/Compress-flag-version.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "utils/exec.h"
#include "utils/test/Tester.h"

#ifndef PROJECT_NAME
#define PROJECT_NAME "not_defined"
#endif
#ifndef PROJECT_VERSION
#define PROJECT_VERSION "not_defined"
#endif

constexpr auto target_binary = "build/bin/compress";

void test_flag_version(Tester& tester) {
    std::cout << "start test_flag_version()" << std::endl;
    const std::string project_name = PROJECT_NAME;
    const std::string project_version = PROJECT_VERSION;

    if (project_name == "not_defined") {
        throw std::runtime_error(std::format("[FAIL] CMake does not define PROJECT_NAME. Got '%s'", PROJECT_NAME));
    }
    if (project_version == "not_defined") {
        throw std::runtime_error(std::format("[FAIL] CMake does not define PROJECT_VERSION. Got '%s'", PROJECT_VERSION));
    }

    const std::string expected = "CRSCE " + project_name + " " + project_version;

    const std::string full_cmd=std::string(target_binary) + " --version";

    std::cout << "test command: " << full_cmd << std::endl;
    if (const std::string output = utils::exec(full_cmd); output.find(expected) != std::string::npos) {
        std::cout << "[PASS] --version output correct: " << output;
        tester.pass();
    } else {
        throw std::runtime_error(std::format("[FAIL] Expected '{}' but got '{}'", expected, output));
    }
}

int main() {
    Tester tester("test/0200_cli/0210_decompress/Compress-flag-version.cpp");
    try {
        std::cout << "compress --version test starting..." << std::endl;
        test_flag_version(tester);
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        tester.fail(e.what());
        return EXIT_FAILURE;
    }
}
