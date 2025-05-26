/**
 * @file 0110_message_roundtrip.cpp
 * @brief Unit test for Gpu::Ipc::Message serialization/deserialization round‐trip (type, kernelId, size, ptr).
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "Common/Buffer8.h"
#include <cstdlib>

using Gpu::Ipc::Response;
using Gpu::Ipc::FailureCodes;
using Common::Buffer8;

int main() {
    Tester tester("0110_message_roundtrip.cpp",ThrowExceptionOnError);

    // Construct a response with error code, payload size, and data
    Response original;
    original.status = FailureCodes::ReadError;
    original.size = 3;
    original.data = Buffer8{0xDE, 0xAD, 0xBE};

    // Serialize and verify buffer length (1 status + 8 size + payload)
    const Buffer8 serialized = original.serialize();
    tester.assertEqual(
        serialized.size(),
        static_cast<size_t>(1 + 8 + original.data.size()),
        "Serialized size should be 9 + payload size"
    );

    // Deserialize and round-trip validate
    Response roundtrip;
    roundtrip.deserialize(serialized);
    tester.assertEqual(
        static_cast<uint8_t>(roundtrip.status),
        static_cast<uint8_t>(original.status),
        "status match"
    );
    tester.assertEqual(
        roundtrip.size,
        original.size,
        "size match"
    );
    tester.assertEqual(
        roundtrip.data,
        original.data,
        "data match"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
