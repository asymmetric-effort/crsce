/**
 * @file utils/generateRandomFile.h
 * @brief generate a file with a given name and size and random content.
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
 * @name generateRandomFile
 * @brief generate a file with a given name and size and random content.
 * @param filename
 * @param file_size
 */
void generateRandomFile(const std::string& filename, const int file_size);
