// file: src/utils/test/deadline.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

/**
 * @brief Set a maximum duration (in seconds) for this test.
 * If the deadline elapses before the test completes, the process exits.
 * @param t Time in seconds until forced termination (default 60s).
 */
void Tester::deadline(unsigned t) {
    // Launch a detached thread that enforces a test timeout
    std::thread([t, self = this]() {
        std::this_thread::sleep_for(std::chrono::seconds(t));
        std::cerr << '[' << self->prefix << "] Test deadline of " << t << " seconds reached. Exiting." << std::endl;
        // Show pass/fail statistics before exiting
        self->showStatistics();
        self->fail();
    }).detach();
}
