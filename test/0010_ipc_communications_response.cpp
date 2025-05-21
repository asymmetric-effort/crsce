// file: test/0010_ipc_communications_response.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Unit test for Gpu::Ipc::Response serialization and deserialization.
 *
 * This test ensures that a Response object can be correctly serialized to a binary buffer
 * and fully reconstructed using `deserialize()`. It confirms field-level equality,
 * correct payload handling, and the use of the fixed header size constant.
 *
 * The test uses a payload of arbitrary binary data and checks:
 * - status field integrity
 * - size field correctness
 * - byte-for-byte payload fidelity
 */

#include "Gpu/Ipc/Response.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstring>

using Gpu::Ipc::Response;

int main() {
    int failures = 0;

    Response original;
    original.status = 0x01;
    original.data = {0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD, 0xF0, 0x0D};
    original.size = original.data.size();

    const std::vector<uint8_t> buffer = original.serialize();

    const size_t expectedSize = Response::kFixedHeaderSize + original.size;
    if (buffer.size() != expectedSize) {
        std::cerr << "[FAIL] Unexpected buffer size: "
                  << buffer.size() << ", expected: "
                  << expectedSize << "\n";
        ++failures;
    }

    try {
        const Response result = Response::deserialize(buffer.data(), buffer.size());

        if (result.status != original.status) {
            std::cerr << "[FAIL] status mismatch\n";
            ++failures;
        }

        if (result.size != original.size) {
            std::cerr << "[FAIL] size mismatch\n";
            ++failures;
        }

        if (result.data != original.data) {
            std::cerr << "[FAIL] payload data mismatch\n";
            ++failures;
        }

    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Exception during deserialization: " << e.what() << "\n";
        ++failures;
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Response serialization test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failure(s).\n";
        return 1;
    }
}
