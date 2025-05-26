/**
* @file src/utils/test/assertNotEqual/assertNotEqual.cpp
 * @brief Defines Tester::assertNotEqual for Gpu::Math::Matrix with tolerance-based comparison.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Math/Matrix.h"
#include <cmath>
#include <sstream>

/**
 * @name assertNotEqual
 * @brief Assert that two matrices are not equal within a given tolerance.
 * @param a First Gpu::Math::Matrix to compare.
 * @param b Second Gpu::Math::Matrix to compare.
 * @param message Message to display on assertion outcome.
 */
void Tester::assertNotEqual(const Gpu::Math::Matrix &a,
                            const Gpu::Math::Matrix &b,
                            const std::string &message) {
    // 1) Shape mismatch → PASS
    if (a.rows() != b.rows() || a.cols() != b.cols()) {
        std::ostringstream oss;
        oss << message
            << " [shape mismatch: "
            << a.rows() << 'x' << a.cols()
            << " != "
            << b.rows() << 'x' << b.cols()
            << "]";
        pass(oss.str());
        return;
    }

    // 2) Element mismatch beyond tolerance → PASS
    for (size_t r = 0; r < a.rows(); ++r) {
        for (size_t c = 0; c < a.cols(); ++c) {
            double v1 = a.at(r, c);
            double v2 = b.at(r, c);
            if (constexpr double tolerance = 1e-9; std::fabs(v1 - v2) > tolerance) {
                std::ostringstream oss;
                oss << message
                    << " [mismatch at (" << r << "," << c << "): "
                    << v1 << " vs " << v2
                    << "]";
                pass(oss.str());
                return;
            }
        }
    }

    // 3) All entries equal within tolerance → FAIL
    fail(message + " [matrices are equal within tolerance]");
}
