/**
 * @file 0111_comm_send_recv_sad.cpp
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
    Tester tester("0111_comm_send_recv_sad.cpp");
    tester.deadline(240);

    tester.debug("create the bidirectional pipes");
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;

    tester.debug("Parent and child communications using the same pipe arrays");
    const Communications parentComm(toChild, fromChild, true);
    const Communications childComm(toChild, fromChild, false);

    tester.debug("Prepare a message to send");
    constexpr Message outMsg = {Gpu::Ipc::CommandType::Write, 0x1111, 0x2222, 0x3333};
    Message inMsg;

    tester.debug("Send the message");
    const Response outResp = {FailureCodes::ReadError,4,{0xDE, 0xAD, 0xBE, 0xEF}};

    // ReSharper disable once CppExpressionWithoutSideEffects
    childComm.send(outResp);
    Response inResp;
    parentComm.recv(inResp);

    tester.assertEqual(
        std::to_underlying(inResp.status),
        std::to_underlying(outResp.status),
        "Response status round-trip");

    tester.assertEqual(inResp.size, outResp.size, "Response size round-trip");
    tester.assertEqual(inResp.data, outResp.data, "Response data round-trip");

    tester.pass();
    return EXIT_SUCCESS;
}
