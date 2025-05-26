/**
 * @file src/utils/test/pass.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name pass
 * @brief increment the passing score
 */
void Tester::pass() {
    passScore++;
}

/**
 * @name pass
 * @brief increment the passing score
 * @param message std::string
 */
void Tester::pass(const std::string &message) {
    debug(message);
    pass();
}
