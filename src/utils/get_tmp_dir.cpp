/**
 * @file src/utils/get_tmp_dir.cpp
 * @brief Declare the get_tmp_dir() function which returns the temporary directory (e.g., /tmp/).
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/get_tmp_dir.h"

/**
 * @name get_tmp_dir
 * @brief return the temp directory (e.g., /tmp) based on operating system.
 * @return std::string
 */
std::string utils::get_tmp_dir() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetTempPathA(MAX_PATH, buffer);
    return std::string(buffer);
#else
    return "/tmp";
#endif
}
