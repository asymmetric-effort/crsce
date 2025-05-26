/**
 * @file src/utils/test/debug.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name debug
 * @brief print debug message
 * @param message std::string
 */
void Tester::debug(const std::string& message) const {
    std::cerr << "[" << prefix << "] " << message << std::endl;
}
