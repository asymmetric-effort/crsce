/**
 * @file include/utils/parse_args.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "utils/struct_CliOptions.h"
#include <vector>

namespace utils {
    /**
     * @function parse_args
     * @brief Generic argument parser over a user-supplied Option list.
     *
     * @param argc   From main().
     * @param argv   From main().
     * @param opts   Vector of CliOptions descriptors.
     * @return EXIT_SUCCESS (0) if parsing ended normally or after --help/--version,
     *         EXIT_FAILURE (non-zero) on parse error or missing required opts.
     */
    int parse_args(const int argc, const char* argv[], const CliOptions& opts);

} // namespace utils
