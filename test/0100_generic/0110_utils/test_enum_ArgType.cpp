/**
* @file test/0100_generic/0110_utils/test_enum_ArgType.cpp
 * @brief Unit tests for utils::ArgType enum
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/enum_ArgType.h"
#include "utils/test/Tester.h"
#include <type_traits>
#include <cstdlib>

int main() {
    Tester tester("utils::ArgType enum");

    // Ensure underlying type is integral
    tester.assertTrue(
        std::is_integral<std::underlying_type<utils::ArgType>::type>::value,
        "Underlying type of ArgType is integral"
    );

    // Check explicit values
    tester.assertTrue(
        static_cast<int>(utils::ArgType::NoValue) == 0,
        "ArgType::NoValue has underlying value 0"
    );
    tester.assertTrue(
        static_cast<int>(utils::ArgType::RequiredValue) == 1,
        "ArgType::RequiredValue has underlying value 1"
    );
    tester.assertTrue(
    static_cast<int>(utils::ArgType::Terminate) == 2,
    "ArgType::Terminate has underlying value 2"
);

    // Verify size is as expected (1 byte or larger)
    tester.assertTrue(
        sizeof(utils::ArgType) <= sizeof(int),
        "Size of ArgType is no greater than size of int"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
