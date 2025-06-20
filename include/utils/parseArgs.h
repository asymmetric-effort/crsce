/**
 * @file include/utils/parseArgs.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#ifndef UTILS_PARSEARGS_H
#define UTILS_PARSEARGS_H

#include "utils/parseArgs.h"
#include "utils/printUsage.h"
#include "utils/printVersion.h"

#include <filesystem>
#include <iostream>
#include <string>

int parse_args(int argc, const char* argv[], std::string &inputFile, std::string &outputFile);

#endif //UTILS_PARSEARGS_H
