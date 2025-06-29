/**
* @file test/0100_generic/0111_utils/test_get_program_name.cpp
 * @brief Unit tests for utils::get_program_name() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/get_program_name.h"
#include "utils/test/Tester.h"
#include <cstdlib>

int main() {
    Tester tester("utils::get_program_name");

    // Case 1: typical path
    const char* argv1[] = {"/usr/local/bin/myapp", nullptr};
    const std::string name1 = utils::get_program_name(argv1);
    tester.assertTrue(name1 == "myapp", "Basename extracted from full path");

    // Case 2: simple name
    const char* argv2[] = {"program", nullptr};
    const std::string name2 = utils::get_program_name(argv2);
    tester.assertTrue(name2 == "program", "Program name unchanged when no path components");

    // Case 3: missing argv[0]
    const char* argv3[] = {nullptr};
    const std::string name3 = utils::get_program_name(argv3);
    tester.assertTrue(name3 == "undefined", "Returns 'undefined' when argv[0] is null");

    tester.pass();
    return EXIT_SUCCESS;
}
