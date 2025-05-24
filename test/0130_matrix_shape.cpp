// file: test/0130_matrix_shape.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0130_matrix_shape.cpp
 * @brief Unit test for Gpu::Math::Matrix constructor and shape accessors.
 *
 * This test validates that:
 *   - The matrix is initialized with correct row and column sizes.
 *   - All entries are initialized to 0.0.
 */

#include "utils/test/Tester.h"
#include "Gpu/Math/Matrix.h"

using Gpu::Math::Matrix;

int main() {
    Tester tester("Gpu::Math::Matrix shape and initialization");

    constexpr std::size_t rows = 4;
    constexpr std::size_t cols = 5;
    Matrix mat(rows, cols);

    tester.assertEqual(mat.rows(), rows, "Row count check");
    tester.assertEqual(mat.cols(), cols, "Column count check");
    tester.assertEqual(mat.data().size(), rows * cols, "Buffer size check");

    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
            tester.assertEqual(mat.at(r, c), 0.0, "Initial value at (" + std::to_string(r) + "," + std::to_string(c) + ")");
        }
    }

    tester.pass();
}
