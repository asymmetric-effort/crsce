// file: test/3000_file-readInputBuffer-verification.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/generateRandomFile.h"
#include "utils/test/Tester.h"
#include "utils/compareFiles.h"
#include "CRSCE/Reader.h"
#include <string>

namespace fs = std::filesystem;

const std::string input_test_file = "build/file-readInputBuffer-verification.input";
const std::string output_test_file = "build/file-readInputBuffer-verification.output";
constexpr size_t test_file_size = 4 * 1024 * 1024; // 4 MiB

int main() {
    Tester tester("test/3000_file-readInputBuffer-verification", TerminateOnError);
    tester.deadline(60);
    tester.skip("disabled for debug");

    tester.debug("Starting...\nGenerating random file.");

    generateRandomFile(input_test_file,test_file_size);

    Reader testCompressor(input_test_file, output_test_file);
    FileBuffer buffer;
    while (testCompressor.readFile(buffer))
        testCompressor.write(buffer);

    tester.assertTrue(compareFiles(input_test_file, output_test_file),"Files should be identical");
}
