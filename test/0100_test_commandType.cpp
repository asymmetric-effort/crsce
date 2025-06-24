/**
 * @file 0100_test_commandType.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
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
    Tester tester("0100_test_commandType.cpp");
    using enum Gpu::Ipc::MessageType;
    const std::map<Gpu::Ipc::MessageType, uint32_t> commands = {
        {Noop, 0x00},
        {Init, 0x01},
        {Alloc, 0x02},
        {Free, 0x03},
        {Write, 0x04},
        {Read, 0x05},
        {RegisterKernel, 0x06},
        {LaunchTask, 0x07},
        {Reset, 0x08},
        {Shutdown, 0x09},
    };
    for (auto [lhs, rhs] : commands) {
        tester.assertEqual(
            static_cast<uint32_t>(lhs),
            static_cast<uint32_t>(rhs),
            std::format("mismatched type (lhs:{},rhs:{})",
                        static_cast<uint32_t>(lhs),
                        rhs));
    }
    tester.pass();
    return EXIT_SUCCESS;
}
