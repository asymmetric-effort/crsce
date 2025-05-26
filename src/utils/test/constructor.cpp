/**
 * @file src/utils/test/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name constructor
 * @brief prints "Tester Initialized" message
 * @param prefix
 * @param onError
 */
Tester::Tester(const std::string& prefix, const ExitOnError onError) : prefix(prefix), onError(onError) {

    std::cerr << "[" << prefix << "] Tester Initialized: " << std::endl;

}
