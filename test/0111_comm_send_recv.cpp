// file: test/0111_comm_send_recv.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0111_comm_send_recv.cpp
 * @brief Unit test for Gpu::Ipc::Communications round-trip for Message and Response.
 *
 * This test sets up a full-duplex pipe pair in a single process to simulate parent/child communication.
 * It sends a Gpu::Ipc::Message from parent to child and a Gpu::Ipc::Response from child to parent, validating:
 *   - Serialization and deserialization integrity
 *   - Role-based access control
 *   - Correct handling of file descriptors and message content
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"

using Gpu::Ipc::Communications;
using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Result;
using Gpu::Ipc::FailureCodes;
using Gpu::Ipc::CommandType;

int main() {
    Tester tester("Gpu::Ipc::Communications message/response send/recv");

    int ptc[2], ctp[2];
    pipe(ptc); // parent-to-child
    pipe(ctp); // child-to-parent

    Communications parent(ptc, ctp, true);
    Communications child(ptc, ctp, false);

    // Parent sends a Message
    Message msg;
    msg.type = CommandType::Write;
    msg.kernelId = 42;
    msg.size = 1024;
    msg.ptr = 0xDEADBEEF;

    const Result send_result = parent.send(msg);
    tester.assertEqual(send_result, Result::Success, "Parent sends Message");

    Message recv_msg;
    const Result recv_result = child.recv(recv_msg);
    tester.assertEqual(recv_result, Result::Success, "Child receives Message");
    tester.assertEqual(static_cast<uint8_t>(recv_msg.type), static_cast<uint8_t>(msg.type), "Type match");
    tester.assertEqual(recv_msg.kernelId, msg.kernelId, "Kernel ID match");
    tester.assertEqual(recv_msg.size, msg.size, "Size match");
    tester.assertEqual(recv_msg.ptr, msg.ptr, "Pointer match");

    // Child sends a Response
    Response res;
    res.status = FailureCodes::Success;
    res.size = 4;
    res.data = {0xAA, 0xBB, 0xCC, 0xDD};

    const Result send_res_result = child.send(res);
    tester.assertEqual(send_res_result, Result::Success, "Child sends Response");

    Response recv_res;
    const Result recv_res_result = parent.recv(recv_res);
    tester.assertEqual(recv_res_result, Result::Success, "Parent receives Response");
    tester.assertEqual(static_cast<uint8_t>(recv_res.status), static_cast<uint8_t>(res.status), "Status match");
    tester.assertEqual(recv_res.size, res.size, "Payload size match");
    tester.assertEqual(recv_res.data, res.data, "Payload content match");

    tester.pass();
}
