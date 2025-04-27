// file: src/cmd/decompress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include "utils/printUsage.h"
#include "utils/printVersion.h"
#include "utils/parseArgs.h"
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    try {
        std::string inputFile;
        std::string outputFile;

        if (const int exit_code=parse_args(argc, argv, inputFile, outputFile); exit_code!=EXIT_SUCCESS)
          return exit_code;

        CRSCE decompressor(inputFile, outputFile);

        if (const int result = decompressor.compress();result == 0) {
            std::cout << "Deompression completed successfully." << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Deompression failed with error code " << result << "." << std::endl;
            return EXIT_FAILURE;
        }
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unhandled unknown exception occurred." << std::endl;
        return EXIT_FAILURE;
    }
}