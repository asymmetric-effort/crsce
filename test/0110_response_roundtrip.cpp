// file: test/0110_response_roundtrip.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0110_response_roundtrip.cpp
 * @brief Unit test for Gpu::Ipc::Response serialization/deserialization round-trip.
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"

using Gpu::Ipc::Response;
using Gpu::Ipc::FailureCodes;

int main() {
    Tester tester("Gpu::Ipc::Response round-trip");

    Response original;
    original.status = FailureCodes::WriteError;
    original.size = 4;
    original.data = {0xDE, 0xAD, 0xBE, 0xEF};

    const auto serialized = original.serialize();
    tester.assertEqual(serialized.size(), 9u + original.data.size(), "Serialized size check");

    Response roundtrip;
    roundtrip.deserialize(serialized);

    tester.assertEqual(static_cast<uint8_t>(roundtrip.status), static_cast<uint8_t>(original.status), "Status match");
    tester.assertEqual(roundtrip.size, original.size, "Payload size match");
    tester.assertEqual(roundtrip.data.size(), original.data.size(), "Data buffer size match");

    for (std::size_t i = 0; i < roundtrip.data.size(); ++i) {
        tester.assertEqual(roundtrip.data[i], original.data[i], "Data byte " + std::to_string(i));
    }

    tester.pass();
}
