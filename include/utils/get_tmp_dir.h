/**
 * @file include/utils/get_tmp_dir.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace utils {
    /**
     * @name get_tmp_dir
     * @brief return the temp directory (e.g., /tmp) based on operating system.
     * @return std::string
     */
    std::string get_tmp_dir();
}

