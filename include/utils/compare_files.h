/**
 * @file utils/compare_files.h
 * @brief Declare a function which will compare two files by file name.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <fstream>

/**
 * @name compare_files
 * @brief Perform a byte-for-byte comparison of two files. (lhs, rhs)
 * @param lhs_file std::string
 * @param rhs_file std::string
 * @return bool
 */
bool compare_files(const std::string& lhs_file, const std::string& rhs_file);
