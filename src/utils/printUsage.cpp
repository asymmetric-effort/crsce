/**
 * @file src/utils/printUsage.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/printUsage.h"

#ifndef COPYRIGHT
#define COPYRIGHT "not_defined"
#endif

/**
 * @name printUsage
 * @brief print a usage banner and return the given exit code
 * @param programName std::string
 * @param exit_code int
 * @return int
 */
int printUsage(const std::string &programName, const int exit_code) {
    std::cout << "\n" << COPYRIGHT << "\n"
            << "Usage: " << programName << " --in <inputfile> --out <outputfile>\n"
            << "Options:\n"
            << "  --in <inputfile>     Specify input file (required)\n"
            << "  --out <outputfile>   Specify output file (required)\n"
            << "  --help               Show this help message\n"
            << "  --version            Show program version\n"
            << std::endl;
    return exit_code;
}
