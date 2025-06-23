/**
* @file 0101_test_message_struct.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"

int main() {
    Tester tester("0101_test_message_struct.cpp");

    auto constexpr expectedCommand = Gpu::Ipc::CommandType::Write;
    auto constexpr expectedKernelId = 0x1234;
    auto constexpr expectedSize = 0x5678u;
    auto constexpr expectedPtr = 0x9876;


    constexpr Gpu::Ipc::Message message = {
        expectedCommand,
        expectedKernelId,
        expectedSize,
        expectedPtr
    };

    tester.assertEqual(
        static_cast<uint32_t>(message.type),
        static_cast<uint32_t>(expectedCommand),
        "commandType mismatch");

    tester.assertEqual(
        static_cast<size_t>(message.size),
        static_cast<size_t>(expectedSize),
        "size mismatch");

    tester.assertEqual(
        static_cast<size_t>(message.ptr),
        static_cast<size_t>(expectedPtr),
        "ptr mismatch");

    tester.assertEqual(
        static_cast<uint32_t>(message.kernelId),
        static_cast<uint32_t>(expectedKernelId),
        "kernelId mismatch");

    tester.pass();
    return EXIT_SUCCESS;
}
