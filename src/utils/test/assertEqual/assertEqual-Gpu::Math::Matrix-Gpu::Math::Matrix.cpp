/**
 * @file src/utils/test/assertEqual/assertEqual-Gpu::Math::Matrix-Gpu::Math::Matrix.cpp
 * @brief Declares an assertion which expects equality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertEqual
 * @brief asserts that a should equal b
 * @param a Gpu::Math::Matrix&
 * @param b Gpu::Math::Matrix&
 * @param message std::string&
 */
void Tester::assertEqual(const Gpu::Math::Matrix& a, const Gpu::Math::Matrix& b, const std::string& msg) {
    if (a.rows() != b.rows() || a.cols() != b.cols()) {
        std::ostringstream oss;
        oss << msg << " [shape mismatch: " << a.rows() << "x" << a.cols()
            << " != " << b.rows() << "x" << b.cols() << "]";
        fail(oss.str());
    }

    for (std::size_t r = 0; r < a.rows(); ++r) {
        for (std::size_t c = 0; c < a.cols(); ++c) {
            if (a.at(r, c) != b.at(r, c)) {
                std::ostringstream oss;
                oss << msg << " [mismatch at (" << r << "," << c << "): "
                    << a.at(r, c) << " != " << b.at(r, c) << "]";
                fail(oss.str());
            }
        }
    }
}
