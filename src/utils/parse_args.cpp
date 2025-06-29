/**
 * @file src/utils/parse_args.cpp
 * @brief Implements utils::parse_args().
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/parse_args.h"
#include "utils/print_usage.h"
#include <iostream>
#include <filesystem>
#include <string>

#include "utils/get_program_name.h"

int utils::parse_args(const int argc,
                      const char* argv[],
                      const CliOption& opts) {
    const std::string program_name = get_program_name(argv);

    for (int i = 1; i < argc; ++i) {
        const std::string this_argument = argv[i];
        bool matched = false;

        for (const auto& [long_name, short_name, arg_type, handler] : opts) {
            if (this_argument == long_name ||
                (short_name && this_argument == std::string{"-"} + short_name)) {
                matched = true;

                if (arg_type == ArgType::NoValue) {
                    // e.g. help/version: handler returns false to stop parsing
                    if (!handler("")) {
                        return EXIT_SUCCESS;
                    }
                }
                else {
                    // consume next token as the value
                    if (i + 1 >= argc) {
                        std::cerr << "Missing value for " << this_argument << "\n";
                        print_usage(program_name);
                        return EXIT_FAILURE;
                    }
                    if (const std::string val = argv[++i]; !handler(val)) {
                        print_usage(program_name);
                        return EXIT_FAILURE;
                    }
                }
                break;
            }
        }

        if (!matched) {
            std::cerr << "Unknown option: " << this_argument << "\n";
            print_usage(program_name);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
