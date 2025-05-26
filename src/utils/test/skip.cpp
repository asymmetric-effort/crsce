/**
 * @file src/utils/test/skip.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name skip
 * @param msg @name skip
 * @brief increment skip score and terminate
 * @param message std::string
 */
void Tester::skip(const std::string& message){
    std::cerr << "[" << prefix << "] Tester::skip() " << message << std::endl;
    skipScore++;
    showStatistics();
    std::exit(EXIT_SUCCESS);
}
