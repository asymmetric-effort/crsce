/**
 * @file 0131_matrix_at.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

/**
 * @file 0131_matrix_at.cpp
 * @brief Unit test for Gpu::Math::Matrix element access and mutation.
 *
 * This test confirms:
 *   - Non-const `at(r, c)` returns writable reference.
 *   - Const `at(r, c)` returns read-only reference.
 *   - Mutations via non-const are reflected in const views.
 *   - Out-of-bounds access throws std::out_of_range.
 */

#include "utils/test/Tester.h"
#include "Gpu/Math/Matrix.h"
#include "Gpu/Exceptions/MatrixOutOfRange.h"

using Gpu::Math::Matrix;

int main() {
    Tester tester("Gpu::Math::Matrix at() read/write and const");

    Matrix mat(3, 3);
    mat.at(1, 2) = 42.5;
    tester.assertEqual(mat.at(1, 2), 42.5, "Write and read at(1,2)");

    mat.at(1, 2) = -7.25;
    tester.assertEqual(mat.at(1, 2), -7.25, "Overwrite at(1,2)");

    // Test const access
    const Matrix& constMat = mat;
    const double value = constMat.at(1, 2);
    tester.assertEqual(value, -7.25, "Const read at(1,2)");

    // Exception: row out-of-bounds
    try {
        (void)mat.at(3, 0);
        tester.fail("Expected exception for row out-of-bounds");
    } catch (const Gpu::Exceptions::MatrixOutOfRange&) {
        tester.pass("Caught row out-of-bounds exception");
    }

    // Exception: column out-of-bounds
    try {
        (void)mat.at(0, 3);
        tester.fail("Expected exception for column out-of-bounds");
    } catch (const Gpu::Exceptions::MatrixOutOfRange&) {
        tester.pass("Caught column out-of-bounds exception");
    }

    tester.pass();
    return EXIT_SUCCESS;
}
