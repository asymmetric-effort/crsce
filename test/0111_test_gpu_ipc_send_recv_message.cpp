/**
 * @file test/0111_test_gpu_ipc_send_recv_message.cpp
 * @brief Test the GPU Abstraction Layer IPC Mechanism
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "../include/Gpu/Ipc/Message/Message.h"
#include "Gpu/Ipc/Channel.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using Gpu::Ipc::Message;
using Gpu::Ipc::Handles;
using Gpu::Ipc::Result;
using Gpu::Ipc::MessageType;
using Common::AbstractPtr;

void child_process(Tester& tester, const Channel& channel) {
    // --- Child: receive a Message, echo it back ---
    tester.debug("child: starting");

    // ReSharper disable once CppLocalVariableMayBeConst
    Message incoming;
    do {
        tester.debug("child: waiting on message...");
        tester.assertEqual(Result::Success, channel.recv(incoming), "child: recv(Message)");
        sleep(1);
        tester.debug("child: received message (need validation)");
        if (incoming.type() == MessageType::Shutdown) {
            tester.debug("child: shutdown recd");
            _exit(EXIT_SUCCESS);
        }
    }
    while (incoming.type() == MessageType::Noop);

    tester.debug("child: message recd echoing");
    tester.assertEqual(Result::Success, channel.send(incoming), "child: send(Message)");
    sleep(1);
    tester.debug("child: message echoed to parent");
    _exit(EXIT_SUCCESS);
}

void parent_process(Tester& tester, const Channel& channel) {
    // --- Parent: send a Message, receive the echo, verify ---
    tester.debug("parent: starting");

    const Message sent(MessageType::Init,/*kernelId=*/123u,/*payload_size=*/4u, AbstractPtr{42});

    tester.debug("parent: Sending Message to child");
    tester.assertEqual(Result::Success, channel.send(sent), "parent: send(Message)");

    tester.debug("parent: Receiving echoed Message from child");
    // ReSharper disable once CppLocalVariableMayBeConst
    Message echoed;
    do {
        tester.debug("parent: waiting on message...");
        tester.assertEqual(Result::Success, channel.recv(echoed), "parent: recv(Message)");
        sleep(1);
        tester.debug("parent: message recd but needs validation");
    }
    while (echoed.type() == MessageType::Noop || echoed.type() == MessageType::Shutdown);

    tester.assertTrue(sent == echoed, "parent: compare message pairs");

    echoed.type(MessageType::Shutdown);

    tester.assertEqual(Result::Success, channel.send(echoed),"shutdown sent");

    tester.pass();
}


int main() {
    Tester tester("0111_test_gpu_ipc_send_recv_message.cpp");
    tester.deadline(300);

    const pid_t pid = fork();
    tester.assertFalse(pid < 0, "fork process");

    // Set up two pipes: parent→child and child→parent
    const Channel channel{};

    if (pid == 0) {
        channel.claimRight(); //righthand side
        // ReSharper disable CppParameterNameMismatch
        child_process(tester, channel);
    }
    else {
        channel.claimLeft(); //lefthand side
        // ReSharper disable CppParameterNameMismatch
        parent_process(tester, channel);
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
