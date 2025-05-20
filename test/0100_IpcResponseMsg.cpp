// file: test/0100_IpcResponseMsg.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/common/IpcResponseMsg.h"
#include "utils/test/Tester.h"
#include <vector>

int main() {
    Tester tester("test/0100_IpcResponseMsg", TerminateOnError);
    tester.deadline(30);

    // Construct original message
    constexpr uint64_t value = 0x12345678ABCDEF00;
    const IpcResponseMsg original(0, &value, sizeof(value));

    // Serialize it
    const auto buffer = original.serialize();
    tester.assertTrue(buffer.size() == 1 + sizeof(uint64_t) + sizeof(value), "Serialized buffer size incorrect");

    // Deserialize back
    const IpcResponseMsg parsed = IpcResponseMsg::deserialize(buffer.data(), buffer.size());
    tester.assertEqual(parsed.status, 0, "Status mismatch after deserialize");
    tester.assertEqual(parsed.size, static_cast<uint64_t>(sizeof(value)), "Payload size mismatch");

    uint64_t parsedVal = parsed.as<uint64_t>();
    tester.assertEqual(parsedVal, value, "Round-trip value mismatch");

    tester.debug("IpcResponseMsg serialization round-trip succeeded.");
    return 0;
}
