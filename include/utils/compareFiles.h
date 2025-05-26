/**
 * @file utils/compareFiles.h
 * @brief Declare a function which will compare two files by file name.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <cstring>
#include <filesystem>

/**
 * @name compareFiles
 * @brief Perform a byte-for-byte comparison of two files.
 * @param file1 std::string
 * @param file2 std::string
 * @return bool
 */
bool compareFiles(const std::string& file1, const std::string& file2);
