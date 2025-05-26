/**
 * @file src/utils/test/fail.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"
#include "utils/test/TestException.h"

/**
 * @name fail
 * @brief update stats and throw a message exception.  OnError (true) terminates execution.
 * @throw TestException
 */
void Tester::fail() {
    failScore++;
    if (onError) {
        showStatistics();
        std::exit(EXIT_FAILURE);
    } else {
        throw TestException("test failed");
    }
}

/**
 * @name fail
 * @brief record message, update stats and throw a message exception.  OnError (true) terminates execution.
 * @param message std::string
 * @throw TestException
 */
void Tester::fail(const std::string &message) {
    failScore++;
    if (onError) {
        showStatistics();
        debug(message);
        std::exit(EXIT_FAILURE);
    } else {
        throw TestException(message);
    }
}
