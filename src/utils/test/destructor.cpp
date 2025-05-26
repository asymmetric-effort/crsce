/**
 * @file src/utils/test/destructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"

/**
 * @name destructor
 * @brief show test statistics and if there were errors, terminate with non-zero exit code.
 */
Tester::~Tester() {
    showStatistics();
    if(failScore > 0) exit(1);
}
