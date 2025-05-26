/**
 * @file src/utils/parseArgs.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/parseArgs.h"

namespace fs = std::filesystem;
/**
 * @name terminate_and_show_usage
 * @brief terminate with the given exit code and print the program usage string.
 * @param program_name std::string
 * @param exit_code int
 * @return int exit_code
 */
int terminate_and_show_usage(const std::string& program_name, const int exit_code=EXIT_FAILURE){
    printUsage(program_name);
    return exit_code;
}

/**
 * @name parse_args
 * @param argc - int
 * @param argv - []char*
 * @param inputFile - std::string
 * @param outputFile - std::string
 * @return int - exit code
 */
int parse_args(const int argc, char* argv[], std::string &inputFile, std::string &outputFile) {

    constexpr std::string argHelp="--help";
    constexpr std::string argVersion="--version";
    constexpr std::string argIn="--in";
    constexpr std::string argOut="--out";
    const std::string program_name(argv[0]);

    if (argc < 2)
        return terminate_and_show_usage(program_name, EXIT_FAILURE);

    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == argHelp) {
            printUsage(program_name);
            return EXIT_SUCCESS;
        } else if (arg == argVersion) {
            return printVersion();
        } else if (arg == argIn && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == argOut && i + 1 < argc) {
            outputFile = argv[++i];
        } else {
            std::cerr << "Unknown or incomplete option: " << arg << std::endl;
            return printUsage(program_name, EXIT_FAILURE);
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

    return EXIT_SUCCESS;
}
