/**
* @file test/0100_generic/0110_utils/test_get_tmp_dir.cpp
 * @brief Unit tests for utils::get_tmp_dir() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/get_tmp_dir.h"
#include "utils/test/Tester.h"
#include <filesystem>
#include <cstdlib>

int main() {
    Tester tester("utils::get_tmp_dir");
    namespace fs = std::filesystem;

    const std::string tmpDir = utils::get_tmp_dir();

    // Common checks: non-empty and exists as directory
    tester.assertTrue(!tmpDir.empty(), "get_tmp_dir returns non-empty string");
    tester.assertTrue(fs::exists(tmpDir), "Temporary directory exists: " + tmpDir);
    tester.assertTrue(fs::is_directory(tmpDir), "Temporary path is a directory");

#ifdef _WIN32
    // On Windows, path should end with a backslash
    tester.assertTrue(tmpDir.back() == '\\' || tmpDir.back() == '/',
        "Windows temp path ends with path separator");
#else
    // On POSIX, expect /tmp
    tester.assertTrue(tmpDir == "/tmp",
        "POSIX temp path equals /tmp");
#endif

    tester.pass();
    return EXIT_SUCCESS;
}
