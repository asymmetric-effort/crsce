/**
 * @file tester_deadline.cpp
 * @brief Verifies that Tester::deadline causes the test process to abort after the specified timeout.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include <thread>
#include <chrono>
#include <cstdlib>

int main() {
    // The following should cause the test to terminate after exceeding the 1-second deadline
    Tester tester("tester_deadline", ThrowExceptionOnError);
    tester.deadline(1, EXIT_SUCCESS);

    // Sleep long enough to trigger deadline
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // If deadline did not abort, fail
    tester.fail("deadline did not terminate the test after 1 second");
    return EXIT_FAILURE;
}
