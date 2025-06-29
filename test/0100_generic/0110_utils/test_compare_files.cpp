/**
 * @file test/0100_generic/0110_utils/test_compare_files.cpp
 * @brief Unit tests for utils::compare_files()
 * @copyright (c) 2025 Asymmetric Effort, LLC.
 */

#include "utils/compare_files.h"
#include "utils/test/Tester.h"
#include <fstream>
#include <random>
#include <vector>
#include <filesystem>
#include <cstdlib>

int main() {
    Tester tester("utils::compare_files");

    const std::string fileA = "fileA.bin";
    const std::string fileB = "fileB.bin";
    const std::string fileC = "fileC.bin";
    const std::string fileD = "fileD.bin";

    // Generate 1KB of random data with fixed seed
    std::mt19937_64 rng(12345);
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    std::vector<unsigned char> dataA(1024);
    for (auto &b : dataA) b = dist(rng);

    // Write fileA and fileB (identical)
    {
        std::ofstream outA(fileA, std::ios::binary);
        outA.write(reinterpret_cast<const char*>(dataA.data()), dataA.size());
    }
    {
        std::ofstream outB(fileB, std::ios::binary);
        outB.write(reinterpret_cast<const char*>(dataA.data()), dataA.size());
    }

    // Write fileC: same prefix but shorter
    {
        std::ofstream outC(fileC, std::ios::binary);
        outC.write(reinterpret_cast<const char*>(dataA.data()), dataA.size() / 2);
    }

    // Generate dataD different content but same size
    std::vector<unsigned char> dataD(1024);
    for (auto &b : dataD) b = dist(rng);
    {
        std::ofstream outD(fileD, std::ios::binary);
        outD.write(reinterpret_cast<const char*>(dataD.data()), dataD.size());
    }

    // Happy path: A vs B
    tester.assertTrue(compare_files(fileA, fileB), "fileA and fileB match");
    // Different size: A vs C
    tester.assertFalse(compare_files(fileA, fileC), "fileA and fileC differ in size");
    // Same size different content: A vs D
    tester.assertFalse(compare_files(fileA, fileD), "fileA and fileD differ in content");

    // Cleanup
    std::filesystem::remove(fileA);
    std::filesystem::remove(fileB);
    std::filesystem::remove(fileC);
    std::filesystem::remove(fileD);

    tester.pass();
    return EXIT_SUCCESS;
}
