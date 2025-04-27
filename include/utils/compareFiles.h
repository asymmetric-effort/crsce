// file: utils/compareFiles.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <cstring>
#include <filesystem>

// compare two files at a byte level.
bool compareFiles(const std::string& file1, const std::string& file2);