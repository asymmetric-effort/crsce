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

    [&tester]()-> void {
        tester.debug("Basic split");
        const std::string s = "a,b,c";
        const auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Basic split yields 3 tokens");
        tester.assertTrue(v[0] == "a" && v[1] == "b" && v[2] == "c", "Tokens are correct");
        tester.pass();
    }();

    [&tester]()-> void {
        tester.debug("Consecutive delimiters");
        const std::string s = "a,,b";
        const auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Consecutive delimiters yield empty token");
        tester.assertTrue(v[0] == "a" && v[1].empty() && v[2] == "b", "Empty token in middle");
        tester.pass();
    }();

    [&tester]()-> void {
        tester.debug("Delimiter at ends");
        const std::string s(",x,");
        const auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 3, "Delimiter at ends yields empty tokens");
        tester.assertTrue(v[0].empty() && v[1] == "x" && v[2].empty(), "Empty tokens at both ends");
        tester.pass();
    }();

    [&tester]()-> void {
        tester.debug("No delimiter");
        const std::string s("hello");
        const auto v = split_string(s, ',');
        tester.assertTrue(v.size() == 1, "No delimiter yields one token");
        tester.assertTrue(v[0] == "hello", "Token matches original string");
        tester.pass();
    }();

    [&tester]()-> void {
        tester.debug("Empty string");
        const std::string s;
        const auto v = split_string(s, ',');
        tester.assertTrue(v.empty(),"expect empty result");
        tester.pass();
    }();
    return EXIT_SUCCESS;
}
