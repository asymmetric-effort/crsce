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

void child_process(Tester& tester, const Handles& sender, const Handles& receiver) {
    // --- Child: receive a Message, echo it back ---
    tester.debug("child: starting");

    const Communications p2c(receiver, sender, false);
    const Communications c2p(sender, receiver, true);

    // ReSharper disable once CppLocalVariableMayBeConst
    Message incoming;
    do {
        tester.debug("child: waiting on message...");
        tester.assertEqual(Result::Success, p2c.recv(incoming), "child: recv(Message)");
        sleep(1);
        tester.debug("child: received message (need validation)");
        if (incoming.type() == CommandType::Shutdown) {
            tester.debug("child: shutdown recd");
            _exit(EXIT_SUCCESS);
        }
    }
    while (incoming.type() == CommandType::Noop);

    tester.debug("child: message recd echoing");
    tester.assertEqual(Result::Success, c2p.send(incoming), "child: send(Message)");
    sleep(1);
    tester.debug("child: message echoed to parent");
    _exit(EXIT_SUCCESS);
}

void parent_process(Tester& tester, const Handles& sender, const Handles& receiver) {
    // --- Parent: send a Message, receive the echo, verify ---
    tester.debug("parent: starting");

    const Communications p2c(sender, receiver, false);
    const Communications c2p(receiver, sender, false);

    const Message sent(CommandType::Init,/*kernelId=*/123u,/*payload_size=*/4u, AbstractPtr{42});

    tester.debug("parent: Sending Message to child");
    tester.assertEqual(Result::Success, p2c.send(sent), "parent: send(Message)");

    tester.debug("parent: Receiving echoed Message from child");
    // ReSharper disable once CppLocalVariableMayBeConst
    Message echoed;
    do {
        tester.debug("parent: waiting on message...");
        tester.assertEqual(Result::Success, c2p.recv(echoed), "parent: recv(Message)");
        sleep(1);
        tester.debug("parent: message recd but needs validation");
    }
    while (echoed.type() == CommandType::Noop || echoed.type() == CommandType::Shutdown);

    tester.assertTrue(sent == echoed, "parent: compare message pairs");

    echoed.type(CommandType::Shutdown);

    tester.assertEqual(Result::Success, c2p.send(echoed),"shutdown sent");

    tester.pass();
}


int main() {
    Tester tester("0111_test_gpu_ipc_send_recv_message.cpp");
    tester.deadline(300);

    // Set up two pipes: parent→child and child→parent
    Handles child{}, parent{};
    tester.assertEqual(pipe(child.data()), 0, "create parent→child pipe");
    tester.assertEqual(pipe(parent.data()), 0, "create child→parent pipe");

    const pid_t pid = fork();
    tester.assertFalse(pid < 0, "fork process");

    if (pid == 0) {
        child_process(tester, child, parent);
    }
    else {
        parent_process(tester, parent, child);
    }
    tester.debug("shutting down...");
    // Wait for child exit status
    int status = 0;
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
