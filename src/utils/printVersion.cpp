/**
 * @file src/utils/printVersion.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/printUsage.h"
#include <iostream>

#ifndef PROJECT_NAME
#define PROJECT_NAME "unknown"
#endif

#ifndef PROJECT_VERSION
#define PROJECT_VERSION "not_defined"
#endif

/**
 * @name printVersion
 * @brief Print the CRSCE version string
 * @return int
 */
int printVersion() {
    std::cout << "CRSCE " << PROJECT_NAME << " " << PROJECT_VERSION << std::endl;
    return EXIT_SUCCESS;
}
