/**
 * @file 0111_comm_send_recv_happy.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <cstdlib>
#include <format>
#include <map>
#include "utils/to_underlying.h"

using Gpu::Ipc::Communications;
using Gpu::Ipc::Message;

int main() {
    using enum Gpu::Ipc::CommandType;
    Tester tester("0111_comm_send_recv_happy.cpp");
    tester.deadline(240);

    tester.debug("create the bidirectional pipes");
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;

    tester.debug("Parent and child communications using the same pipe arrays");
    const Communications parentComm(toChild, fromChild, true);
    const Communications childComm(toChild, fromChild, false);

    tester.debug("Prepare a message to send");
    constexpr Message outMsg = {Write, 1337, 684867, 5948};
    Message inMsg;

    tester.debug("Send the message");
    // ReSharper disable once CppExpressionWithoutSideEffects
    parentComm.send(outMsg);
    tester.debug("Message sent.  Verify it is still intact");

    tester.assertEqual(
        static_cast<uint32_t>(outMsg.type),
        static_cast<uint32_t>(Write),
        "Message kernelId");

    tester.assertEqual(
        outMsg.kernelId,
        static_cast<uint32_t>(1337),
        "Message kernelId");

    tester.assertEqual(
        outMsg.size,
        static_cast<size_t>(684867),
        "Message size");

    tester.assertEqual(
        outMsg.ptr,
        static_cast<size_t>(5948),
        "Message ptr");

    tester.debug("Recv the message");
    childComm.recv(inMsg);
    tester.debug("Message received");

    tester.assertEqual(
        std::to_underlying(inMsg.type),
        std::to_underlying(outMsg.type),
        std::format("Message type round-trip lhs:{} rhs:{}",
                    std::to_underlying(inMsg.type),
                    std::to_underlying(outMsg.type)
        )
    );
    tester.assertEqual(std::to_underlying(inMsg.type), std::to_underlying(Write), "Message type");
    tester.assertEqual(inMsg.kernelId, outMsg.kernelId, "Message kernelId round-trip");
    tester.assertEqual(inMsg.size, outMsg.size, "Message size round-trip");
    tester.assertEqual(inMsg.ptr, outMsg.ptr, "Message ptr round-trip");

    tester.pass();
    return EXIT_SUCCESS;
}
