/**
 * @file src/utils/parse_args.cpp
 * @brief Implements utils::parse_args().
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/parse_args.h"
#include "utils/print_usage.h"
#include "utils/struct_CliOptions.h"
#include <iostream>
#include <filesystem>
#include <string>

#include "utils/get_program_name.h"

inline bool match_args(const std::string& this_argument, const std::string& long_arg, const char short_arg) {
    return this_argument == long_arg || (short_arg && this_argument == std::string{"-"} + short_arg);
}

int utils::parse_args(const int argc, const char* argv[], const utils::CliOptions& opts) {
    const std::string program_name = get_program_name(argv);

    for (int i = 1; i < argc; ++i) {
        const std::string this_argument = argv[i];
        bool matched = false;

        // ReSharper disable once CppUseStructuredBinding
        for (const auto& opt : opts) {
            if (matched = match_args(this_argument, opt.long_name, opt.short_name); matched) {
                if (opt.processing_style == utils::ProcessingStyle::Terminate)
                    return !opt.handler("");
                if (opt.arg_type == ArgType::NoValue) {
                    if (!opt.handler("")) return EXIT_FAILURE;
                } else {
                    if (i + 1 >= argc) {
                        // consume next token as the value
                        std::cerr << "Missing value for " << this_argument << "\n";
                        print_usage(program_name);
                        return EXIT_FAILURE;
                    }
                    if (const std::string val = argv[++i]; !opt.handler(val)) {
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
