/**
 * @file src/utils/test/deadline.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>

/**
 * @brief Set a maximum duration (in seconds) for this test.
 * If the deadline elapses before the test completes, the process exits immediately.
 * @param t Time in seconds until forced termination (default 60s).
 * @param exit_code_on_deadline
 */
void Tester::deadline(unsigned t, int exit_code_on_deadline) {
    std::jthread([t, this, exit_code_on_deadline]() {
        std::this_thread::sleep_for(std::chrono::seconds(t));
        std::cerr << '[' << prefix << "] Test deadline of " << t
                  << " seconds reached. Exiting." << std::endl;
        showStatistics();
        // Immediately terminate without throwing exceptions or calling destructors
        std::_Exit(exit_code_on_deadline);
    }).detach();
}
