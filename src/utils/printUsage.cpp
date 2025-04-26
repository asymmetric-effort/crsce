// file: src/utils/printUsage.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/printUsage.h"

#ifndef COPYRIGHT
#define COPYRIGHT "not_defined"
#endif

void printUsage(const std::string& programName) {
    std::cout << "\n" << COPYRIGHT <<"\n"
              << "Usage: " << programName << " --in <inputfile> --out <outputfile>\n"
              << "Options:\n"
              << "  --in <inputfile>     specify input file (required)\n"
              << "  --out <outputfile>   specify output file (required)\n"
              << "  --help        Show this help message\n"
              << "  --version     Show program version\n"
              << std::endl;
}
