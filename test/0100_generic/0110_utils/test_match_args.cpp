/**
* @file test/0100_generic/0110_utils/test_match_args.cpp
 * @brief Unit tests for utils::match_args() using Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/match_args.h"
#include "utils/test/Tester.h"
#include <cstdlib>

int main() {
    Tester tester("utils::match_args");

    // Long form matches
    tester.assertTrue(
        utils::match_args("--option", "--option", 'o'),
        "Long form '--option' matches"
    );

    // Short form matches
    tester.assertTrue(
        utils::match_args("-o", "--option", 'o'),
        "Short form '-o' matches"
    );

    // Mismatch when neither form matches
    tester.assertFalse(
        utils::match_args("--other", "--option", 'o'),
        "Unknown '--other' does not match"
    );

    // Short_arg = 0 disables short matching
    tester.assertFalse(
        utils::match_args("-o", "--option", '\0'),
        "Short form disabled when short_arg is '\\0'"
    );

    // Partial or malformed strings should not match
    tester.assertFalse(
        utils::match_args("option", "--option", 'o'),
        "Missing leading dashes does not match"
    );
    tester.assertFalse(
        utils::match_args("-option", "--option", 'o'),
        "Single dash + full name does not match"
    );
    tester.assertFalse(
        utils::match_args("--o", "--option", 'o'),
        "Invalid long form abbreviation does not match"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
