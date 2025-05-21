// file: test/0010_ipc_communications_message.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file
 * @brief Unit test for Gpu::Ipc::Message serialization and deserialization.
 *
 * This test confirms that a Message object can be serialized to a binary buffer
 * and accurately reconstructed using `deserialize()`. The original and reconstructed
 * objects are compared field-by-field to ensure fidelity.
 *
 * It also validates the reported fixed size of the serialized format.
 */

#include "Gpu/Ipc/Message.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>

using Gpu::Ipc::Message;

int main() {
    int failures = 0;

    Message original;
    original.type     = 0xDEADBEEF;
    original.kernelId = 0xCAFEBABE;
    original.size     = 0x123456789ABCDEF0;
    original.ptr      = 0x0FEDCBA987654321;

    const std::vector<uint8_t> buffer = original.serialize();

    if (buffer.size() != Message::kFixedSize) {
        std::cerr << "[FAIL] Unexpected buffer size: "
                  << buffer.size() << ", expected: "
                  << Message::kFixedSize << "\n";
        ++failures;
    }

    try {
        auto [type, kernelId, size, ptr] = Message::deserialize(buffer.data(), buffer.size());

        if (type != original.type) {
            std::cerr << "[FAIL] type mismatch\n";
            ++failures;
        }

        if (kernelId != original.kernelId) {
            std::cerr << "[FAIL] kernelId mismatch\n";
            ++failures;
        }

        if (size != original.size) {
            std::cerr << "[FAIL] size mismatch\n";
            ++failures;
        }

        if (ptr != original.ptr) {
            std::cerr << "[FAIL] ptr mismatch\n";
            ++failures;
        }

    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Exception during deserialization: " << e.what() << "\n";
        ++failures;
    }

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Message serialization test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failure(s).\n";
        return 1;
    }
}
