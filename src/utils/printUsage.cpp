// file: src/utils/printUsage.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/printUsage.h"


void printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " --in <inputfile> --out <outputfile>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help        Show this help message" << std::endl;
    std::cout << "  --version     Show program version" << std::endl;
}
