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

int printVersion() {
    const std::string project_name(PROJECT_NAME);
    const std::string project_version(PROJECT_VERSION);
    std::cout << "CRSCE " << project_name << " " << project_version << std::endl;
    return EXIT_SUCCESS;
}
