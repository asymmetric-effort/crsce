/**
 * @file src/utils/parse_args.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/parse_args.h"
#include "utils/terminate_and_show_usage.h"



int utils::parse_args(int argc,
                      const char* argv[],
                      const char* prog,
                      const std::vector<Option>& opts) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        bool matched = false;
        for (auto const& opt : opts) {
            if (arg == opt.long_name || (opt.short_name && arg == std::string{"-"} + opt.short_name)) {
                matched = true;
                // no‐value flag?
                if (opt.arg_type == ArgType::NoValue) {
                    if (!opt.handler("")) return EXIT_SUCCESS;  // help/version
                } else {
                    if (++i >= argc) {
                        std::cerr << "Missing value for " << arg << "\n";
                        print_usage(prog);
                        return EXIT_FAILURE;
                    }
                    if (!opt.handler(argv[i])) {
                        print_usage(prog);
                        return EXIT_FAILURE;
                    }
                }
                break;
            }
        }
        if (!matched) {
            std::cerr << "Unknown option: " << arg << "\n";
            print_usage(prog);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
