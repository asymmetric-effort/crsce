// file: src/cmd/compress.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "CRSCE/CRSCE.h"
#include "utils/printUsage.h"
#include "utils/printVersion.h"
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

        if (argc < 2) {
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--help") {
                printUsage(argv[0]);
                return EXIT_SUCCESS;
            } else if (arg == "--version") {
                printVersion();
                return EXIT_SUCCESS;
            } else if (arg == "--in" && i + 1 < argc) {
                inputFile = argv[++i];
            } else if (arg == "--out" && i + 1 < argc) {
                outputFile = argv[++i];
            } else {
                std::cerr << "Unknown or incomplete option: " << arg << std::endl;
                printUsage(argv[0]);
                return EXIT_FAILURE;
            }
        }

        if (inputFile.empty() || outputFile.empty()) {
            std::cerr << "Error: Both --in and --out must be specified." << std::endl;
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }

        if (!fs::exists(inputFile)) {
            std::cerr << "Error: Input file '" << inputFile << "' does not exist." << std::endl;
            return EXIT_FAILURE;
        }

        if (fs::exists(outputFile)) {
            std::cerr << "Error: Output file '" << outputFile << "' already exists. Refusing to overwrite." << std::endl;
            return EXIT_FAILURE;
        }

        CRSCE compressor(inputFile, outputFile);
        int result = compressor.compress();

        if (result == 0) {
            std::cout << "Compression completed successfully." << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Compression failed with error code " << result << "." << std::endl;
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