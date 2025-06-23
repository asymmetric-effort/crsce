/**
 * @file 0112_comm_partial_recv.cpp
 * @brief Verifies that Communications::recv throws when given a truncated Message or Response payload.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <cstdint>

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::CommandType;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("0112_comm_partial_recv.cpp");

    // Set up bidirectional pipes
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;
    if (pipe(toChild.data()) < 0 || pipe(fromChild.data()) < 0) {
        return EXIT_FAILURE;
    }
    const Communications parentComm(toChild, fromChild, true);
    const Communications childComm(toChild, fromChild, false);

    // ---- Partial Message receive ----
    Message outMsg;
    outMsg.type     = CommandType::Write;
    outMsg.kernelId = 0x1010;
    outMsg.size     = 0x2020;
    outMsg.ptr      = 0x3030;
    const auto msgBuf = outMsg.serialize();
    // Write only a truncated header (less than full 24 bytes)
    write(toChild[1], msgBuf.data(), msgBuf.size() - 5);
    tester.expectException<TestException>([&] {
        childComm.recv(outMsg);
    });

    // ---- Partial Response receive ----
    Response outResp;
    outResp.status = FailureCodes::ReadError;
    outResp.size   = 4;
    outResp.data   = {0xAA, 0xBB, 0xCC, 0xDD};
    const auto respBuf = outResp.serialize();
    // Write only part of the response (missing payload bytes)
    write(fromChild[1], respBuf.data(), respBuf.size() - 2);
    tester.expectException<TestException>([&] {
        parentComm.recv(outResp);
    });

    tester.pass();
    return EXIT_SUCCESS;
}
