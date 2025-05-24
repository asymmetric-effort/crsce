// file: src/utils/test/assertEqual/assertEqual-$i-$i.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

void Tester::assertEqual(const Common::Buffer64& a, const Common::Buffer64& b, const std::string& msg) {
    if (a.size() != b.size()) {
        std::ostringstream oss;
        oss << msg << " [size mismatch: " << a.size() << " != " << b.size() << "]";
        fail(oss.str());
    }

    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            std::ostringstream oss;
            oss << msg << " [mismatch at byte " << i << ": "
                << std::hex << static_cast<int>(a[i])
                << " != " << static_cast<int>(b[i]) << "]";
            fail(oss.str());
        }
    }
}
