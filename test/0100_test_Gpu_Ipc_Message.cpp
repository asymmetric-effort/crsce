/**
* @file 0100_test_Gpu_Ipc_Message.cpp
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
#include <ranges>
#include <typeinfo>

using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Communications;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("0100_test_Gpu_Ipc_Message.cpp");
    using enum Gpu::Ipc::MessageType;
    for (auto a = 0; a < 2; a++) {
        for (auto b = 0; b < 2; b++) {
            for (auto c = 0; c < 2; c++) {
                for (auto d = 0; d < 2; d++) {
                    constexpr std::array expectedCommand = {
                        Init, Alloc, Free, Write, Read, RegisterKernel, LaunchTask, Reset, Shutdown,
                    };
                    constexpr std::array<uint32_t, 2> expectedKernelIds = {0x00, 0xFFFFFFFF};
                    constexpr std::array<Common::AbstractPtr, 2> expectedPtrs = {0x00, 0xFFFFFFFFFFFFFFFF};
                    constexpr std::array<uint32_t, 2> expectedSizes = {0x00, 0xFFFFFFFF};

                    auto const thisKernelId = expectedKernelIds.at(a);
                    auto const thisPtr = expectedPtrs.at(b);
                    auto const thisSize = expectedSizes.at(c);
                    auto const thisCommand = expectedCommand.at(d);

                    const Message testMsg = {
                        thisCommand,
                        thisKernelId,
                        thisSize,
                        thisPtr
                    };
                    tester.assertEqual(testMsg.kernelId(), thisKernelId,
                                       std::format("Kernel Id ({}) mismatch", thisKernelId));
                    tester.assertEqual(testMsg.kernelId(), thisKernelId, std::format("Sizes ({}) mismatch", thisSize));
                    tester.assertEqual(testMsg.kernelId(), thisKernelId, std::format("Pointer ({}) mismatch", thisPtr));
                }
            }
        }
    }
    tester.pass();
    return EXIT_SUCCESS;
}
