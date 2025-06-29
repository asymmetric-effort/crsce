/**
* @file test/0100_generic/0110_utils/test_generate_temp_filename.cpp
 * @brief Unit tests for utils::generate_temp_filename() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/generate_temp_filename.h"
#include "utils/test/Tester.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>

int main() {
    Tester tester("utils::generate_temp_filename");

    using namespace std::filesystem;

    const std::string prefix = "generate_temp_filename_test";
    const std::string extension = ".txt";
    // Generate two filenames and ensure they are distinct and non-existing
    std::string tmp1 = utils::generate_temp_filename(prefix, extension);
    std::string tmp2 = utils::generate_temp_filename(prefix, extension);

    tester.assertTrue(!tmp1.empty(), "generate_temp_filename returns non-empty");
    tester.assertTrue(!tmp2.empty(), "generate_temp_filename returns non-empty on second call");
    tester.assertTrue(tmp1 != tmp2, "Two generated temp filenames are distinct");

    // Ensure neither file exists
    tester.assertFalse(exists(tmp1), "Temp file 1 does not exist yet");
    tester.assertFalse(exists(tmp2), "Temp file 2 does not exist yet");

    // Create the first file, then generate a third temp name, ensure no collision
    {
        std::ofstream out(tmp1);
        tester.assertTrue(out.is_open(), "Able to create temp file 1");
    }
    std::string tmp3 = utils::generate_temp_filename(prefix, extension);
    tester.assertTrue(!tmp3.empty(), "generate_temp_filename returns non-empty after creation");
    tester.assertTrue(tmp3 != tmp1 && tmp3 != tmp2, "Generated temp filename does not collide with existing ones");

    // Cleanup
    std::error_code ec;
    std::filesystem::remove(tmp1, ec);
    if (exists(tmp3)) std::filesystem::remove(tmp3, ec);
    if (exists(tmp2)) std::filesystem::remove(tmp2, ec);

    tester.pass();
    return EXIT_SUCCESS;
}
