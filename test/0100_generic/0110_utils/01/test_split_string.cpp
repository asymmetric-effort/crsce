/**
* @file test/0100_generic/0110_utils/test_split_string.cpp
 * @brief Unit tests for utils::split_string() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/split_string.h"
#include "utils/test/Tester.h"
#include <vector>
#include <string>
#include <cstdlib>

int main() {
    Tester tester("utils::split_string");

    using utils::split_string;

    // 1) Basic split
    {
        const std::string s = "a,b,c";
        auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Basic split yields 3 tokens");
        tester.assertTrue(v[0] == "a" && v[1] == "b" && v[2] == "c", "Tokens are correct");
    }

    // 2) Consecutive delimiters
    {
        const std::string s = "a,,b";
        auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Consecutive delimiters yield empty token");
        tester.assertTrue(v[0] == "a" && v[1].empty() && v[2] == "b", "Empty token in middle");
    }

    // 3) Delimiter at ends
    {
        const std::string s = ",x,";
        auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Delimiter at ends yields empty tokens");
        tester.assertTrue(v[0].empty() && v[1] == "x" && v[2].empty(), "Empty tokens at both ends");
    }

    // 4) No delimiter
    {
        const std::string s = "hello";
        auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 1, "No delimiter yields one token");
        tester.assertTrue(v[0] == "hello", "Token matches original string");
    }

    // 5) Empty string
    {
        const std::string s;
        auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 1, "Empty string yields one empty token");
        tester.assertTrue(v[0].empty(), "Token is empty string");
    }

    tester.pass();
    return EXIT_SUCCESS;
}
