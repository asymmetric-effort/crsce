/**
 * @file test/0100_generic/0110_utils/test_parse_args.cpp
 * @brief End‐to‐end tests for utils::parse_args() using the Tester framework
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/parse_args.h"
#include "utils/struct_CliOptions.h"
#include "utils/enum_ArgType.h"
#include "utils/get_program_name.h"
#include "utils/print_usage.h"
#include "utils/test/Tester.h"

#include <cstdlib>
#include <string>
#include <vector>

int main() {
    Tester tester("utils::parse_args");

    /**
     * Prepare a simple option set:
     * --foo / -f requires a value, sets fooVal
     * --bar / -b is no-value, toggles barFlag
     */
    std::string fooVal;
    bool barFlag = false;
    const std::vector<utils::Option> opts = {
        {
            "--foo", 'f', utils::ArgType::RequiredValue,
            [&](const std::string& v) {
                fooVal = v;
                return true;
            }
        },
        {
            "--bar", 'b', utils::ArgType::NoValue,
            [&](const std::string&) {
                barFlag = true;
                return false; // simulate immediate exit
            }
        }
    };

    // 1) No args → should succeed, no side effects
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", nullptr};
        const int rc = utils::parse_args(1, argv, opts);
        tester.assertTrue(rc == EXIT_SUCCESS, "No args → EXIT_SUCCESS");
        tester.assertTrue(fooVal.empty(), "fooVal unchanged");
        tester.assertTrue(!barFlag, "barFlag unchanged");
    }

    // 2) Required‐value happy path
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", "--foo", "value", nullptr};
        const int rc = utils::parse_args(3, argv, opts);
        tester.assertTrue(rc == EXIT_SUCCESS, "'--foo value' → EXIT_SUCCESS");
        tester.assertTrue(fooVal == "value", "fooVal set correctly");
        tester.assertTrue(!barFlag, "barFlag unchanged");
    }

    // 3) Missing value for --foo → failure
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", "--foo", nullptr};
        const int rc = utils::parse_args(2, argv, opts);
        tester.assertTrue(rc == EXIT_FAILURE, "Missing value → EXIT_FAILURE");
    }

    // 4) No‐value flag triggers immediate exit → failure
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", "--bar", nullptr};
        const int rc = utils::parse_args(2, argv, opts);
        tester.assertTrue(rc == EXIT_FAILURE, "No‐value handler returns false → EXIT_FAILURE");
        tester.assertTrue(barFlag, "barFlag set by handler");
    }

    // 5) Short variants: -f works, but -b causes exit → failure
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", "-f", "abc", "-b", nullptr};
        const int rc = utils::parse_args(4, argv, opts);
        tester.assertTrue(rc == EXIT_FAILURE, "Short flags -f and -b should exit → EXIT_FAILURE");
        tester.assertTrue(fooVal == "abc", "fooVal set by -f before exit");
        tester.assertTrue(barFlag, "barFlag set by -b before exit");
    }

    // 6) Unknown flag → failure
    {
        fooVal.clear();
        barFlag = false;
        const char* argv[] = {"prog", "--unknown", nullptr};
        const int rc = utils::parse_args(2, argv, opts);
        tester.assertTrue(rc == EXIT_FAILURE, "Unknown flag → EXIT_FAILURE");
    }

    tester.pass();
    return EXIT_SUCCESS;
}
