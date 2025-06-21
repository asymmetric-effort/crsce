/**
 * @file 0110_response_roundtrip.cpp
 * @brief Unit test for Gpu::Ipc::Response serialization/deserialization round‐trip (status, size, payload).
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */


#include "utils/test/Tester.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/FailureCodes.h"
#include "utils/to_underlying.h"

using Gpu::Ipc::Response;
using Gpu::Ipc::FailureCodes;
using Common::Buffer8;

int main() {
    Tester tester("0110_response_roundtrip.cpp", ThrowExceptionOnError);

    // Construct a response with error code, payload size, and data
    Response original;
    original.status = FailureCodes::ReadError;
    original.size   = 3;
    original.data   = Buffer8{0xDE, 0xAD, 0xBE};

    // Serialize and verify buffer length (1 byte status + 8 bytes size + payload)
    const Buffer8 serialized = original.serialize();
    tester.assertEqual(
        serialized.size(),
        static_cast<size_t>(1 + 8 + original.data.size()),
        "Serialized length should be 1(status)+8(size)+payload"
    );

    // Deserialize and round-trip validate
    Response roundtrip;
    roundtrip.deserialize(serialized);
    tester.assertEqual(
        std::to_underlying(roundtrip.status),
        std::to_underlying(original.status),
        "status match"
    );
#if SIZE_MAX != UINT64_MAX
    tester.assertEqual(
        roundtrip.size,
        original.size,
        "size match"
    );
#endif
    tester.assertEqual(
        roundtrip.data,
        original.data,
        "data match"
    );

    tester.pass();
    return EXIT_SUCCESS;
}
