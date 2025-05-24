// file: test/0110_message_roundtrip.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0110_message_roundtrip.cpp
 * @brief Unit test for Gpu::Ipc::Message serialization/deserialization round-trip.
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"

using Gpu::Ipc::Message;
using Gpu::Ipc::CommandType;

int main() {
    Tester tester("Gpu::Ipc::Message round-trip");

    Message original;
    original.type     = CommandType::Write;
    original.kernelId = 0xCAFEBABE;
    original.size     = 0x1234567890;
    original.ptr      = 0xABCDEF0000112233;

    const auto serialized = original.serialize();
    tester.assertEqual(serialized.size(), static_cast<size_t>(24u), "Serialized size should be 24 bytes");

    Message roundtrip;
    roundtrip.deserialize(serialized);

    tester.assertEqual(static_cast<uint8_t>(roundtrip.type), static_cast<uint8_t>(original.type), "CommandType match");
    tester.assertEqual(roundtrip.kernelId, original.kernelId, "kernelId match");
    tester.assertEqual(roundtrip.size, original.size, "size match");
    tester.assertEqual(roundtrip.ptr, original.ptr, "ptr match");

    tester.pass();
}
