/**
 * @file 0100_test_initial_state.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "../include/Gpu/Ipc/Message/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "Gpu/Ipc/Communications.h"
#include <unistd.h>
#include <cstdlib>
#include <format>
#include <map>

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("0100_test_initial_state.cpp");

    constexpr int closed = -1;

    // Create bidirectional pipes
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;

    tester.assertNotEqual(pipe(toChild.data()),closed, "expect toChild -1 initial state");
    tester.assertNotEqual(pipe(fromChild.data()),closed, "expect fromChild -1 initial state");
    tester.pass();
    return EXIT_SUCCESS;
}
