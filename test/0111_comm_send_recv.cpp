// file: test/0111_comm_send_recv.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <cstdlib>
#include <cstdint>

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("0111_comm_send_recv.cpp");

    // Create bidirectional pipes
    int toChild[2], fromChild[2];
    if (pipe(toChild) < 0 || pipe(fromChild) < 0) {
        return EXIT_FAILURE;
    }

    // Parent and child communications using the same pipe arrays
    Communications parentComm(toChild, fromChild, true);
    Communications childComm(toChild, fromChild, false);

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

    tester.assertEqual(static_cast<uint8_t>(inMsg.type), static_cast<uint8_t>(outMsg.type), "Message type round-trip");
    tester.assertEqual(inMsg.kernelId, outMsg.kernelId, "Message kernelId round-trip");
    tester.assertEqual(inMsg.size, outMsg.size, "Message size round-trip");
    tester.assertEqual(inMsg.ptr, outMsg.ptr, "Message ptr round-trip");

    // ---- Response send/recv ----
    Response outResp;
    outResp.status = FailureCodes::ReadError;
    outResp.size   = 4;
    outResp.data   = {0xDE, 0xAD, 0xBE, 0xEF};

    // ReSharper disable once CppExpressionWithoutSideEffects
    childComm.send(outResp);
    Response inResp;
    parentComm.recv(inResp);

    tester.assertEqual(static_cast<uint8_t>(inResp.status), static_cast<uint8_t>(outResp.status), "Response status round-trip");
    tester.assertEqual(inResp.size, outResp.size, "Response size round-trip");
    tester.assertEqual(inResp.data, outResp.data, "Response data round-trip");

    tester.pass();
    return EXIT_SUCCESS;
}
