/**
* @file 0101_test_message_serialize.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"

int main() {
    Tester tester("0101_test_message_serialize.cpp");

    auto constexpr expectedPtr = 0x9876;
    auto constexpr expectedSize = 0x5678u;
    auto constexpr expectedKernelId = 0x1234;
    auto constexpr expectedCommand = Gpu::Ipc::CommandType::Write;

    constexpr Gpu::Ipc::Message expected = {
        expectedCommand,
        expectedKernelId,
        expectedSize,
        expectedPtr
    };

    auto const serializedMessage = expected.serialize();

    Gpu::Ipc::Message actual;
    actual.deserialize(serializedMessage);

    tester.assertEqual(
        static_cast<uint32_t>(actual.type),
        static_cast<uint32_t>(expected.type),
        "type mismatch");

    tester.assertEqual(
        static_cast<uint32_t>(actual.kernelId),
        static_cast<uint32_t>(expected.kernelId),
        "kernelId mismatch");

    tester.assertEqual(
        static_cast<uint32_t>(actual.size),
        static_cast<uint32_t>(expected.size),
        "size mismatch");

    tester.assertEqual(
        static_cast<uint32_t>(actual.ptr),
        static_cast<uint32_t>(expected.ptr),
        "ptr mismatch");

    tester.pass();
    return EXIT_SUCCESS;
}
