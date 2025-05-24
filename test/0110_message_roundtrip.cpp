// file: test/0110_message_roundtrip.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0110_message_roundtrip.cpp
 * @brief Unit test for Gpu::Ipc::Message serialization/deserialization round-trip.
 *
 * This test verifies that a Gpu::Ipc::Message object can be serialized into a binary
 * format and reconstructed without loss of fidelity. The test checks:
 *   - That the serialized buffer is exactly 24 bytes
 *   - That all fields (type, kernelId, size, ptr) are preserved through the round-trip
 *   - That no padding, truncation, or transformation corrupts the result
 *
 * This ensures correctness of the fixed-size message protocol used to communicate
 * between the Emulator and MockGpu processes.
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"

using Gpu::Ipc::Message;
using Gpu::Ipc::CommandType;

int main() {
    Tester tester("Gpu::Ipc::Message round-trip");

    Message original;
    original.type = CommandType::Write;
    original.kernelId = 0xCAFEBABE;
    original.size = 0x1234567890;
    original.ptr = 0xABCDEF0000112233;

    const auto serialized = original.serialize();

    tester.assertEqual(serialized.size(), static_cast<size_t>(24u), "Serialized size should be 24 bytes");

    const Message roundtrip = Message::deserialize(serialized.data(), serialized.size());

    tester.assertEqual(static_cast<uint8_t>(roundtrip.type), static_cast<uint8_t>(original.type), "CommandType match");
    tester.assertEqual(roundtrip.kernelId, original.kernelId, "kernelId match");
    tester.assertEqual(roundtrip.size, original.size, "size match");
    tester.assertEqual(roundtrip.ptr, original.ptr, "ptr match");

    tester.pass();
}
