// file: test/0111_communication_send_recv_message_happy.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <sys/wait.h>
#include <format>

using Gpu::Ipc::Message;
using Gpu::Ipc::Communications;
using Gpu::Ipc::Handles;
using Gpu::Ipc::Result;
using Gpu::Ipc::CommandType;

/**
 * @brief Validate that a message matches the expected fields.
 *
 * @param tester the active Tester instance
 * @param msg the message to validate
 * @param type expected command type
 * @param kid expected kernelId
 * @param size expected size field
 * @param ptr expected ptr field
 */
void validate(Tester &tester, const Message &msg, CommandType type, const uint32_t kid, const size_t size,
              const size_t ptr) {
    tester.assertEqual(static_cast<uint8_t>(msg.type), static_cast<uint8_t>(type), "CommandType mismatch");
    tester.assertEqual(msg.kernelId, kid, "kernelId mismatch");
    tester.assertEqual(msg.size, size, "size mismatch");
    tester.assertEqual(msg.ptr, ptr, "ptr mismatch");
}

int main() {
    Tester tester("0111_communication_send_recv_message_happy.cpp");
    tester.deadline(240);

    Handles parentToChild;
    Handles childToParent;

    if (pipe(parentToChild.data()) < 0 || pipe(childToParent.data()) < 0) {
        tester.fail("pipe() failed");
        return EXIT_FAILURE;
    }

    const pid_t pid = fork();
    if (pid < 0) {
        tester.fail("fork() failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Child: receive and validate 5 messages
        const Communications p2c(parentToChild, childToParent, false);
        for (int i = 0; i < 5; ++i) {
            Message msg;
            if (p2c.recv(msg) != Result::Success) {
                _exit(EXIT_FAILURE);
            }
            Tester child("child/validator");
            validate(child, msg, CommandType::Write, i, i * 1024, i * 64);
            child.pass(std::format("child received message {}", i));
        }
        _exit(EXIT_SUCCESS);
    } else {
        // Parent: send 5 messages
        const Communications c2p(childToParent, parentToChild, false);
        for (int i = 0; i < 5; ++i) {
            Message msg{
                CommandType::Write,
                static_cast<uint32_t>(i),
                static_cast<uint32_t>(i * 1024),
                static_cast<size_t>(i * 64)
            };

            validate(tester, msg, CommandType::Write, i, i * 1024, i * 64);
            if (const auto result = c2p.send(msg); result != Result::Success) {
                tester.fail(std::format("send({}) failed: {}", i, static_cast<int>(result)));
                return EXIT_FAILURE;
            }
            tester.pass(std::format("parent sent message {}", i));
        }

        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            tester.pass("child process exited cleanly");
            return EXIT_SUCCESS;
        } else {
            tester.fail("child process failed or crashed");
            return EXIT_FAILURE;
        }
    }
}
