#include "utils/printUsage.h"

//
// We should expect that PROJECT_VERSION is configured by cmake.
//
#ifndef PROJECT_VERSION
#define PROJECT_VERSION "not_defined"
#endif

void printVersion() {
    std::cout << "CRSCE Compressor " << PROJECT_VERSION << std::endl;
}
