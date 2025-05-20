// file: test/3000_file-readInputBuffer-verification.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <string>
#include "CRSCE/Reader.h"
#include "utils/compareFiles.h"
#include "utils/generateRandomFile.h"

namespace fs = std::filesystem;

const std::string input_test_file = "build/file-readInputBuffer-verification.input";
const std::string output_test_file = "build/file-readInputBuffer-verification.output";
constexpr size_t test_file_size = 4 * 1024 * 1024; // 4 MiB

int main() {
    try {

        std::cout << "Starting...\n"
                  << "Generating random file."
                  << std::endl;

        generateRandomFile(input_test_file,test_file_size);

        {
            Reader testCompressor(input_test_file, output_test_file);
            FileBuffer buffer;
            while (testCompressor.readFile(buffer)) {
                testCompressor.write(buffer);
            }
        }

        if (compareFiles(input_test_file, output_test_file)) {
            std::cout << "[PASS] Files are identical." << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cerr << "[FAIL] Files are different." << std::endl;
            return EXIT_FAILURE;
        }

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
