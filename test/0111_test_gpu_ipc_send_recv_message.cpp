/**
 * @file test/0111_test_gpu_ipc_send_recv_message.cpp
 * @brief Test the GPU Abstraction Layer IPC Mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using Gpu::Ipc::Message;
using Gpu::Ipc::Communications;
using Gpu::Ipc::Handles;
using Gpu::Ipc::Result;
using Gpu::Ipc::CommandType;
using Common::AbstractPtr;

int main() {
    Tester tester("0111_test_gpu_ipc_send_recv_message.cpp");
    tester.deadline(120);

    // Set up two pipes: parent→child and child→parent
    Handles toChild{}, fromChild{};
    tester.assertNotEqual(pipe(toChild.data()), 0, "Failed to create parent→child pipe");
    tester.assertNotEqual(pipe(fromChild.data()), 0, "Failed to create child→parent pipe");

    const pid_t pid = fork();
    if (pid < 0) {
        tester.fail("fork() failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // --- Child: receive a Message, echo it back ---
        tester.debug("child: starting");

        const Communications p2c(toChild, fromChild, false);
        const Communications c2p(fromChild, toChild, false);

        // ReSharper disable once CppLocalVariableMayBeConst
        Message incoming;
        do {
            tester.debug("child: waiting on message...");
            tester.assertEqual(Result::Success, p2c.recv(incoming), "child: recv(Message) should succeed");
            sleep(1);
            tester.debug("child: received message (need validation)");
        }
        while (incoming.type() == CommandType::Noop);

        tester.debug("child: message recd echoing");
        tester.assertEqual(Result::Success, c2p.send(incoming), "child: send(Message) should succeed");
        sleep(1);
        tester.debug("child: message echoed to parent");
        _exit(EXIT_SUCCESS);
    }
    else {
        // --- Parent: send a Message, receive the echo, verify ---
        tester.debug("parent: starting");

        const Communications p2c(toChild, fromChild, false);
        const Communications c2p(fromChild, toChild, false);

        const Message sent(CommandType::Init,/*kernelId=*/123u,/*payload_size=*/4u, AbstractPtr{42});

        tester.debug("parent: Sending Message to child");
        tester.assertEqual(Result::Success, p2c.send(sent), "parent: send(Message) should succeed");

        tester.debug("parent: Receiving echoed Message from child");
        // ReSharper disable once CppLocalVariableMayBeConst
        Message echoed;
        do {
            tester.debug("parent: waiting on message...");
            tester.assertEqual(Result::Success, c2p.recv(echoed), "parent: recv(Message) should succeed");
            sleep(1);
            tester.debug("parent: message recd but needs validation");
        }
        while (echoed.type() == CommandType::Noop);

        tester.assertTrue(sent == echoed, "parent: Echoed Message must match the original");

        tester.pass();

        // Wait for child exit status
        int status = 0;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
}
