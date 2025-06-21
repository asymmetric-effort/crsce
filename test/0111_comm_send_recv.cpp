/**
 * @file 0111_comm_send_recv.cpp
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

#include "utils/to_underlying.h"

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("0111_comm_send_recv.cpp");

    // Create bidirectional pipes
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;
    if (pipe(toChild.data()) < 0 || pipe(fromChild.data()) < 0) {
        return EXIT_FAILURE;
    }

    // Parent and child communications using the same pipe arrays
    const Communications parentComm(toChild, fromChild, true);
    const Communications childComm(toChild, fromChild, false);

    // ---- Message send/recv ----
    Message outMsg;
    outMsg.type     = Gpu::Ipc::CommandType::Write;
    outMsg.kernelId = 0x1111;
    outMsg.size     = 0x2222;
    outMsg.ptr      = 0x3333;

    // ReSharper disable once CppExpressionWithoutSideEffects
    parentComm.send(outMsg);
    Message inMsg;
    childComm.recv(inMsg);

    tester.assertEqual(
        std::to_underlying(inMsg.type),
        std::to_underlying(outMsg.type),
        "Message type round-trip");

    tester.assertEqual(
        inMsg.kernelId,
        outMsg.kernelId,
        "Message kernelId round-trip");

#if SIZE_MAX != UINT64_MAX
    tester.assertEqual(inMsg.size, outMsg.size, "Message size round-trip");
    tester.assertEqual(inMsg.ptr, outMsg.ptr, "Message ptr round-trip");
#endif

    // ---- Response send/recv ----
    Response outResp;
    outResp.status = FailureCodes::ReadError;
    outResp.size   = 4;
    outResp.data   = {0xDE, 0xAD, 0xBE, 0xEF};

    // ReSharper disable once CppExpressionWithoutSideEffects
    childComm.send(outResp);
    Response inResp;
    parentComm.recv(inResp);

    tester.assertEqual(
        std::to_underlying(inResp.status),
        std::to_underlying(outResp.status),
        "Response status round-trip");

#if SIZE_MAX != UINT64_MAX
    tester.assertEqual(inResp.size, outResp.size, "Response size round-trip");
#endif
    tester.assertEqual(inResp.data, outResp.data, "Response data round-trip");

    tester.pass();
    return EXIT_SUCCESS;
}
