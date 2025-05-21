// file: test/0015_ipc_communications_class.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Integration test for Gpu::Ipc::Communications.
 *
 * This test verifies:
 *  - Successful round-trip message passing between parent and child.
 *  - Proper enforcement of role-based access controls:
 *      - parentSend() and parentRecv() only usable by parent.
 *      - childSend() and childRecv() only usable by child.
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

        // Negative test: parentSend() should not be allowed in child
        Message invalidMsg;
        if (comm.parentSend(invalidMsg) != Result::Error) {
            std::cerr << "[CHILD FAIL] parentSend() should fail in child\n";
            _exit(1);
        }

        // Negative test: parentRecv() should not be allowed in child
        Response dummy;
        if (comm.parentRecv(dummy) != Result::Error) {
            std::cerr << "[CHILD FAIL] parentRecv() should fail in child\n";
            _exit(1);
        }

        // Positive path
        Message msg;
        if (comm.childRecv(msg) != Result::Success) {
            std::cerr << "[CHILD FAIL] childRecv failed\n";
            _exit(1);
        }

        if (msg.type != 42 || msg.size != 123456789 || msg.ptr != 0xABCDEF) {
            std::cerr << "[CHILD FAIL] Message content mismatch\n";
            _exit(1);
        }

        Response resp;
        resp.status = 0;
        resp.data = {0xBE, 0xEF};
        resp.size = resp.data.size();

        if (comm.childSend(resp) != Result::Success) {
            std::cerr << "[CHILD FAIL] childSend failed\n";
            _exit(1);
        }

        _exit(0);

    } else {
        // ---------------- PARENT PROCESS ----------------

        // Negative test: childSend() should not be allowed in parent
        Response invalidResp;
        if (comm.childSend(invalidResp) != Result::Error) {
            std::cerr << "[PARENT FAIL] childSend() should fail in parent\n";
            ++failures;
        }

        // Negative test: childRecv() should not be allowed in parent
        Message dummyMsg;
        if (comm.childRecv(dummyMsg) != Result::Error) {
            std::cerr << "[PARENT FAIL] childRecv() should fail in parent\n";
            ++failures;
        }

        // Positive path
        Message msg;
        msg.type = 42;
        msg.kernelId = 1;
        msg.size = 123456789;
        msg.ptr = 0xABCDEF;

        if (comm.parentSend(msg) != Result::Success) {
            std::cerr << "[PARENT FAIL] parentSend failed\n";
            ++failures;
        }

        Response resp;
        if (comm.parentRecv(resp) != Result::Success) {
            std::cerr << "[PARENT FAIL] parentRecv failed\n";
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
            std::cerr << "[PARENT FAIL] child exited abnormally\n";
            ++failures;
        }
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Communications full test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failure(s).\n";
        return 1;
    }
}
