/**
 * @file test/0100_generic/0111_CliOptions/CliOptions.cpp
 * @brief Unit tests for utils::Option struct and CliOptions alias
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/enum_ArgType.h"
#include "utils/struct_CliOptions.h"
#include "utils/test/Tester.h"
#include <type_traits>
#include <vector>
#include <string>

int main() {
    Tester tester("test/0100_generic/0111_CliOptions/CliOptions.cpp");

    using namespace utils;

    // Verify CliOptions is alias for std::vector<Option>
    tester.assertTrue(
        std::is_same_v<CliOptions, std::vector<Option>>,
        "CliOptions is std::vector<Option>"
    );

    // Construct an Option instance and verify its fields
    bool handler_called = false;
    const Option opt{
        "--test",       // long_name
        't',             // short_name
        ArgType::NoValue,// arg_type
        [&](const std::string &val) {
            handler_called = true;
            return val.empty();  // true if val is empty
        }
    };

    // Check field values
    tester.assertTrue(opt.long_name == "--test", "Option.long_name stored correctly");
    // ReSharper disable once CppDFAConstantConditions
    tester.assertTrue(opt.short_name == 't',      "Option.short_name stored correctly");
    // ReSharper disable once CppDFAConstantConditions
    tester.assertTrue(opt.arg_type == ArgType::NoValue, "Option.arg_type stored correctly");

    // Test handler behavior
    handler_called = false;
    const bool result_empty = opt.handler("");  // empty val => true
    tester.assertTrue(handler_called && result_empty,
                       "Option.handler returns true and called for empty val");

    handler_called = false;
    const bool result_nonempty = opt.handler("value");
    tester.assertTrue(handler_called && !result_nonempty,
                       "Option.handler returns false and called for non-empty val");

    // Test CliOptions container usage
    CliOptions opts;
    opts.push_back(opt);
    tester.assertTrue(opts.size() == 1, "CliOptions can contain Option instances");
    tester.assertTrue(opts[0].long_name == "--test", "CliOptions stores Option correctly");

    tester.pass();
    return EXIT_SUCCESS;
}
