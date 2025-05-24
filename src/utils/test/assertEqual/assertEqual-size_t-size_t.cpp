// file: src/utils/test/assertEqual-size_t-size_t.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(size_t a, size_t b, const std::string &message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}
