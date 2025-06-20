/**
* @file include/utils/terminate_and_show_usage.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once
#include "utils/parseArgs.h"
#include <filesystem>
#include <string>

/**
* @name terminate_and_show_usage
 * @brief terminate with the given exit code and print the program usage string.
 * @param program_name std::string
 * @param exit_code int
 * @return int exit_code
 */
int terminate_and_show_usage(const std::string& program_name, const int exit_code=EXIT_FAILURE);
