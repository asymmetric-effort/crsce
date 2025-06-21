/**
 * @file 0111_comm_send_recv_happy.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <cstdlib>
#include <cstdint>
#include <format>
#include <map>

#include "utils/to_underlying.h"

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::FailureCodes;

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
    constexpr Message outMsg = {Write, 0x1111, 0x2222, 0x3333};
    Message inMsg;

    tester.debug("Send the message");
    // ReSharper disable once CppExpressionWithoutSideEffects
    parentComm.send(outMsg);
    tester.debug("Recv the message");
    childComm.recv(inMsg);

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
