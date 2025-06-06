/**
 * @file src/utils/test/assertNotEqual-Common-Buffer64.cpp
 * @brief Defines Tester::assertNotEqual overload for Common::Buffer64 payload comparisons.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include <sstream>

/**
 * @name assertNotEqual
 * @brief Assert that two Common::Buffer64 objects are not equal.
 * @param a First buffer to compare.
 * @param b Second buffer to compare.
 * @param message Message to display on assertion outcome.
 */
void Tester::assertNotEqual(const Common::Buffer64 &a,
                            const Common::Buffer64 &b,
                            const std::string &message) {
    // 1) Size mismatch → PASS
    if (a.size() != b.size()) {
        std::ostringstream oss;
        oss << message << " [size mismatch: " << a.size() << " != " << b.size() << "]";
        pass(oss.str());
        return;
    }

    // 2) Element mismatch → PASS
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            std::ostringstream oss;
            oss << message << " [mismatch at index " << i << ": "
                    << static_cast<int>(a[i]) << " != " << static_cast<int>(b[i]) << "]";
            pass(oss.str());
            return;
        }
    }

    // 3) All entries equal → FAIL
    fail(std::format("{} [buffers are equal]",message));
}
