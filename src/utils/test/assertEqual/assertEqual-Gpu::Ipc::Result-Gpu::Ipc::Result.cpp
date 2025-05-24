// file: src/utils/test/assertEqual/assertEqual-$i-$i.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

void Tester::assertEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string& message) {
    assertEqual(static_cast<uint8_t>(a), static_cast<uint8_t>(b), message);
}
