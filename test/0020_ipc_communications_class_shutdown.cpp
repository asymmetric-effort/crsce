// file: test/0020_ipc_communications_class_shutdown.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Test shutdown behavior of Gpu::Ipc::Communications.
 *
 * This test ensures that after the destructor is invoked on a Communications
 * instance, all send operations return Result::Shutdown and are no-ops.
 *
 * It uses fork() to create parent and child contexts, initializes the
 * Communications instance, immediately destroys it, then attempts to send.
 */

#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace Gpu::Ipc;

int main() {
    int failures = 0;

    pid_t child_pid = fork();
    if (child_pid < 0) {
        std::cerr << "[FAIL] fork() failed\n";
        return 1;
    }

    if (child_pid == 0) {
        // ---------------- CHILD PROCESS ----------------
        Result shutdownResult = Result::Error;

        {
            Communications comm(0);  // PID is 0 in the child
            // trigger destructor immediately
        }

        // Now create dummy instance and try childSend()
        Communications comm(0);
        Response dummy;
        shutdownResult = comm.childSend(dummy);

        if (shutdownResult != Result::Shutdown) {
            std::cerr << "[CHILD FAIL] childSend after shutdown returned "
                      << shutdownResult << ", expected Shutdown\n";
            _exit(1);
        }

        _exit(0);
    } else {
        // ---------------- PARENT PROCESS ----------------
        Result shutdownResult = Result::Error;

        {
            Communications comm(child_pid);
            // trigger destructor immediately
        }

        // Now create dummy instance and try parentSend()
        Communications comm(child_pid);
        Message dummy;
        shutdownResult = comm.parentSend(dummy);

        if (shutdownResult != Result::Shutdown) {
            std::cerr << "[PARENT FAIL] parentSend after shutdown returned "
                      << shutdownResult << ", expected Shutdown\n";
            ++failures;
        }

        int status = 0;
        waitpid(child_pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            std::cerr << "[PARENT FAIL] child exited abnormally\n";
            ++failures;
        }
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Communications shutdown behavior test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failure(s).\n";
        return 1;
    }
}
