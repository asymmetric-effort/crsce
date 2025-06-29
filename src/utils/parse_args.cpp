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
                      const std::vector<Option>& opts) {

    const std::string program_name = get_program_name(argv);

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        bool matched = false;

        for (const auto& opt : opts) {
            const auto& long_name  = opt.long_name;
            const char  short_name = opt.short_name;
            const auto  arg_type   = opt.arg_type;
            const auto& handler    = opt.handler;

            if (arg == long_name ||
                (short_name && arg == std::string{"-"} + short_name)) {
                matched = true;

                if (arg_type == ArgType::NoValue) {
                    // e.g. help/version: handler returns false to stop parsing
                    if (!handler("")) {
                      return EXIT_SUCCESS;
                    }
                } else {
                    // consume next token as the value
                    if (i + 1 >= argc) {
                        std::cerr << "Missing value for " << arg << "\n";
                        print_usage(program_name);
                        return EXIT_FAILURE;
                    }
                    const std::string val = argv[++i];
                    if (!handler(val)) {
                        print_usage(program_name);
                        return EXIT_FAILURE;
                    }
                }
                break;
            }
        }

        if (!matched) {
            std::cerr << "Unknown option: " << arg << "\n";
            print_usage(program_name);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
