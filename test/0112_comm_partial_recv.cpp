// file: test/0112_comm_partial_recv.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0112_comm_partial_recv.cpp
 * @brief Test Gpu::Ipc::Communications behavior when receiving truncated data.
 *
 * This test manually writes a partial `Gpu::Ipc::Message` into the pipe to simulate
 * stream truncation or protocol desynchronization. It validates that the receiving
 * side correctly returns Result::IOError instead of deserializing garbage or hanging.
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Result.h"

#include <unistd.h>

using Gpu::Ipc::Communications;
using Gpu::Ipc::Message;
using Gpu::Ipc::Result;

int main() {
    Tester tester("Gpu::Ipc::Communications partial recv");

    int ptc[2], ctp[2];
    pipe(ptc);  // parent to child
    pipe(ctp);  // child to parent

    Communications parent(ptc, ctp, true);
    const Communications child(ptc, ctp, false);

    // Write a truncated message from parent manually (e.g., 12 bytes instead of full 24)
    constexpr uint8_t partial[12] = {0x01, 0x02, 0x03};  // corrupted or incomplete message
    const ssize_t n = write(ptc[1], partial, 12);
    tester.assertEqual(static_cast<unsigned>(n), 12u, "Wrote partial message to pipe");

    Message out;
    const Result result = child.recv(out);

    tester.assertEqual(result, Result::IOError, "recv() should fail on incomplete message");

    tester.pass();
}
