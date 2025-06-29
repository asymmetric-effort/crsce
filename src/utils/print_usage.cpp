/**
 * @file src/utils/print_usage.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/print_usage.h"

#ifndef COPYRIGHT
#define COPYRIGHT "not_defined"
#endif
namespace utils {
    int print_usage(const std::string& programName, const int exit_code) {
        const std::string copyright_string(COPYRIGHT);
        std::cout << "\n" << copyright_string << "\n"
            << "Usage: " << programName << " --in <inputfile> --out <outputfile>\n"
            << "Options:\n"
            << "  --in <inputfile>     specify input file (required)\n"
            << "  --out <outputfile>   specify output file (required)\n"
            << "  --help        Show this help message\n"
            << "  --version     Show program version\n"
            << std::endl;
        return exit_code;
    }
}
