/**
 * @file src/utils/generate_temp_filename.cpp
 * @brief Declare a function which will generate a temporary filename with a given prefix and extension.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/generate_temp_filename.h"
#include "utils/get_tmp_dir.h"
#include <random>
#include <sstream>
#include <iostream>

namespace utils {
    /**
     * @name generate_temp_filename
     * @brief generate a temporary filename with a given prefix and extension.
     * @param prefix
     * @param ext
     * @return std::string
     */
    std::string generate_temp_filename(const std::string &prefix, const std::string &ext) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution dist(10000, 99999);

        std::ostringstream oss;
        oss << get_tmp_dir() << "/" << prefix << "_" << dist(gen) << "." << ext;
        return oss.str();
    }
}
