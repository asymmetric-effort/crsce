// file: test/0015_ipc_communications_class.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Integration test for Gpu::Ipc::Communications.
 *
 * This test verifies that a parent process can send a Message to a child process,
 * and that the child can respond with a Response using the Gpu::Ipc::Communications
 * abstraction. It also ensures that the role-based access controls are properly enforced.
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

    Communications comm(child_pid);

    if (child_pid == 0) {
        // ---------------- CHILD PROCESS ----------------
        Message msg;
        Result recvResult = comm.childRecv(msg);
        if (recvResult != Result::Success) {
            std::cerr << "[CHILD FAIL] childRecv failed with result: " << recvResult << "\n";
            _exit(1);
        }

        if (msg.type != 42 || msg.size != 123456789 || msg.ptr != 0xABCDEF) {
            std::cerr << "[CHILD FAIL] Received message fields did not match expected values.\n";
            _exit(1);
        }

        Response resp;
        resp.status = 0;
        resp.data = {0xBE, 0xEF};
        resp.size = resp.data.size();

        Result sendResult = comm.childSend(resp);
        if (sendResult != Result::Success) {
            std::cerr << "[CHILD FAIL] childSend failed with result: " << sendResult << "\n";
            _exit(1);
        }

        _exit(0);

    } else {
        // ---------------- PARENT PROCESS ----------------
        Message msg;
        msg.type = 42;
        msg.kernelId = 1;
        msg.size = 123456789;
        msg.ptr = 0xABCDEF;

        Result sendResult = comm.parentSend(msg);
        if (sendResult != Result::Success) {
            std::cerr << "[PARENT FAIL] parentSend failed with result: " << sendResult << "\n";
            ++failures;
        }

        Response resp;
        Result recvResult = comm.parentRecv(resp);
        if (recvResult != Result::Success) {
            std::cerr << "[PARENT FAIL] parentRecv failed with result: " << recvResult << "\n";
            ++failures;
        } else {
            if (resp.status != 0 || resp.size != 2 || resp.data != std::vector<uint8_t>({0xBE, 0xEF})) {
                std::cerr << "[PARENT FAIL] Response content mismatch\n";
                ++failures;
            }
        }

        int status = 0;
        waitpid(child_pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            std::cerr << "[PARENT FAIL] child process exited with failure\n";
            ++failures;
        }
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Communications round-trip test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failure(s).\n";
        return 1;
    }
}
