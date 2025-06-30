/**
 * @file src/utils/parse_args.cpp
 * @brief Implements utils::parse_args().
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/parse_args.h"
#include "utils/struct_CliOptions.h"
#include "utils/get_program_name.h"
#include "utils/print_usage.h"
#include "utils/match_args.h"
#include <iostream>
#include <string>

/**
 * @name parse_args
 * @brief parse commandline arguments and update the caller's state via the handler functions.
 * @param argc const int
 * @param argv const argument string array
 * @param opts commandline argument option descriptor vector
 * @return int exit code (0: success, non-zero: error)
 */
int utils::parse_args(const int argc, const char* argv[], const CliOptions& opts) {
    const std::string program_name = get_program_name(argv);

    constexpr int first_arg_index = 1; // we start with 1 because index 0 is the program name
    for (int arg_index = first_arg_index; arg_index < argc; ++arg_index) {
        const std::string arg = argv[arg_index];
        bool matched = false;

        // ReSharper disable once CppUseStructuredBinding
        for (auto const& opt : opts) {
            if (matched = match_args(arg, opt.long_name, opt.short_name); !matched)
                continue;

            switch (opt.arg_type) {
            case ArgType::Terminate: {
                // e.g. --help or --version: handler prints and signals exit
                const bool ok = opt.handler("");
                return ok ? EXIT_SUCCESS : EXIT_FAILURE;
            }

            case ArgType::NoValue: {
                // e.g. --debug, --noop: handler toggles state
                if (!opt.handler("")) {
                    // handler signals failure
                    return EXIT_FAILURE;
                }
                break; // continue parsing further flags
            }

            case ArgType::RequiredValue: {
                // e.g. --file <path>
                if (arg_index + 1 >= argc) {
                    std::cerr << program_name << ": Missing value for " << arg << "\n";
                    print_usage(program_name);
                    return EXIT_FAILURE;
                }
                if (const std::string val = argv[++arg_index]; !opt.handler(val)) {
                    print_usage(program_name);
                    return EXIT_FAILURE;
                }
                break;
            }
            } //end switch
            break; // once handled, stop scanning opts and move to the next arg
        }

        if (!matched) {
            std::cerr << program_name << ": Unknown option: " << arg << "\n";
            print_usage(program_name);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
