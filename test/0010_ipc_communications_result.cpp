// file: test/0010_ipc_communications_result.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Ipc/Result.h"
#include <iostream>
#include <string>

using Gpu::Ipc::Result;

int main() {
    int failures = 0;

    auto test = [&](Result r, const std::string& expected) {
        std::string actual = resultToString(r);
        if (actual != expected) {
            std::cerr << "[FAIL] Result " << static_cast<int>(r)
                      << ": expected '" << expected
                      << "', got '" << actual << "'\n";
            ++failures;
        }
    };

    test(Result::Success,  "Success");
    test(Result::Empty,    "Empty");
    test(Result::Blocked,  "Blocked");
    test(Result::Shutdown, "Shutdown");
    test(Result::Error,    "Error");

    if (failures == 0) {
        std::cout << "[PASS] Gpu::Ipc::Result enum test passed.\n";
        return 0;
    } else {
        std::cout << "[FAIL] " << failures << " failures.\n";
        return 1;
    }
}
