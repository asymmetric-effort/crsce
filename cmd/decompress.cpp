/**
 * @file decompress.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "CRSCE/CRSCE.h"
#include "utils/print_usage.h"
#include "utils/print_version.h"
#include "utils/parse_args.h"
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <string>

#include "utils/get_program_name.h"

int main(const int argc, const char** argv) {
    std::filesystem::path inFile; // filename of the uncompressed input
    std::filesystem::path outFile; // filename to which compressed output will be written
    size_t concurrency = 1; // the number of concurrent blocks to be processed at one time.

    constexpr uint32_t min_concurrency{1}; //The minimum number of blocks to process at a given time.
    constexpr uint32_t max_concurrency{1024}; //The maximum number of blocks ot process at a given time.

    const utils::CliOptions options = {
        {
            "--help", 'h', utils::ArgType::Terminate,
            [&argv](auto) {
                utils::print_usage(utils::get_program_name(argv));
                return false;
            },
        },
        {
            "--version", 'v', utils::ArgType::Terminate,
            [](auto) {
                utils::print_version();
                return false;
            },
        },
        {
            "--in", 'i', utils::ArgType::RequiredValue,
            [&inFile](auto argument_value) {
                inFile = argument_value;
                if (inFile.empty()) {
                    std::cerr << "Error: --in is required.\n";
                    return false;
                }
                if (!std::filesystem::exists(inFile)) {
                    std::cerr << "Error: --in <file> must specify an existing file.\n";
                    return false;
                }
                return true;
            },
        },
        {
            "--out", 'o', utils::ArgType::RequiredValue,
            [&outFile](auto argument_value) {
                outFile = argument_value;
                if (outFile.empty()) {
                    std::cerr << "Error: --out is required.\n";
                    return false;
                }
                if (std::filesystem::exists(outFile)) {
                    std::cerr << "Error: " << outFile << " exists.  Cannot overwrite.\n";
                    return false;
                }
                return true;
            },
        },
        {
            "--concurrency", 'c', utils::ArgType::RequiredValue,
            [&concurrency](const auto& argument_value) {
                concurrency = std::stoul(argument_value);
                if (concurrency < min_concurrency || concurrency > max_concurrency) {
                    std::cerr << "Error: --concurrency is invalid. "
                        << "It must be between "
                        << std::to_string(min_concurrency)
                        << " and " << std::to_string(max_concurrency) << ".\n";
                    return false;
                }
                return true;
            },
        }
    };


    /**
     * Call utils::parse_args() to parse the above options using their respective
     * handler functions.  Terminate if necessary.
     */
    if (utils::parse_args(argc, argv, options) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    /**
     * Run the compressor, passing in block_size and concurrency
     */
    try {
        if (inFile.empty()) throw std::invalid_argument("Input file must be provided. Use -h for help");
        if (outFile.empty()) throw std::invalid_argument("Output file must be provided. Use -h for help");
        CRSCE compressor(inFile, outFile, 512, concurrency);
        if (const int rc = compressor.decompress(); rc == 0) {
            std::cout << "Compression completed successfully.\n";
            return EXIT_SUCCESS;
        } else {
            std::cerr << "Compression failed with error code " << rc << ".\n";
            return EXIT_FAILURE;
        }
    } catch (const std::invalid_argument& e){
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unhandled unknown exception occurred.\n";
        return EXIT_FAILURE;
    }
}
