// file: test/0101_test_message_serialize.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include <vector>
#include <cstdint>
#include <format>

int main()
{
    Tester tester("0101_test_message_serialize.cpp");

    const Common::AbstractPtr expectedPtr      = static_cast<Common::AbstractPtr>(0x9876);
    const size_t              expectedSize     = static_cast<size_t>(0x5678u);
    const uint32_t            expectedKernelId = static_cast<uint32_t>(0u); // Write commands ignore kernelId
    const Gpu::Ipc::CommandType expectedCommand = Gpu::Ipc::CommandType::Write;

    // Verify type widths
    tester.assertTrue(
        sizeof(expectedSize) == 8,
        std::format("size_t should be 64-bit not {}", sizeof(expectedSize)));
    tester.assertTrue(
        sizeof(expectedPtr) == 8,
        std::format("Common::AbstractPtr should be 64-bit not {}", sizeof(expectedPtr)));
    tester.assertTrue(
        sizeof(expectedCommand) == 4,
        std::format("Gpu::Ipc::CommandType should be 32-bit not {}", sizeof(expectedCommand)));

    // Construct message
    const Gpu::Ipc::Message msg(expectedCommand,
                                 expectedKernelId,
                                 expectedSize,
                                 expectedPtr);

    // Build expected byte sequence
    const uint32_t cmd_int = static_cast<uint32_t>(expectedCommand);
    const uint32_t kid_int = expectedKernelId;
    const uint64_t size64  = expectedSize;
    const uint64_t ptr64   = expectedPtr;

    std::vector<uint8_t> expected_bytes = {
        // CommandType (4 bytes, little endian)
        static_cast<uint8_t>( cmd_int        & 0xFF),
        static_cast<uint8_t>((cmd_int >>  8) & 0xFF),
        static_cast<uint8_t>((cmd_int >> 16) & 0xFF),
        static_cast<uint8_t>((cmd_int >> 24) & 0xFF),
        // KernelId (4 bytes, little endian)
        static_cast<uint8_t>( kid_int        & 0xFF),
        static_cast<uint8_t>((kid_int >>  8) & 0xFF),
        static_cast<uint8_t>((kid_int >> 16) & 0xFF),
        static_cast<uint8_t>((kid_int >> 24) & 0xFF),
        // size     (8 bytes, little endian)
        static_cast<uint8_t>( size64         & 0xFF),
        static_cast<uint8_t>((size64  >>  8) & 0xFF),
        static_cast<uint8_t>((size64  >> 16) & 0xFF),
        static_cast<uint8_t>((size64  >> 24) & 0xFF),
        static_cast<uint8_t>((size64  >> 32) & 0xFF),
        static_cast<uint8_t>((size64  >> 40) & 0xFF),
        static_cast<uint8_t>((size64  >> 48) & 0xFF),
        static_cast<uint8_t>((size64  >> 56) & 0xFF),
        // ptr      (8 bytes, little endian)
        static_cast<uint8_t>( ptr64          & 0xFF),
        static_cast<uint8_t>((ptr64   >>  8) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 16) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 24) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 32) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 40) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 48) & 0xFF),
        static_cast<uint8_t>((ptr64   >> 56) & 0xFF)
    };

    // Serialize message
    const auto actual_serialized = msg.serialize();

    // Compare byte-for-byte
    tester.assertEqual(actual_serialized,expected_bytes,"Byte-for-byte mismatch");

    tester.pass();
    return EXIT_SUCCESS;
}
