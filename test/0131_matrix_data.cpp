// file: test/0131_matrix_data.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

/**
 * @file 0131_matrix_data.cpp
 * @brief Unit test for Gpu::Math::Matrix::data() accessors.
 *
 * This test verifies:
 *   - `data()` returns a reference to the underlying buffer.
 *   - Mutations via `.data()` affect matrix state.
 *   - Read-back from `at()` reflects changes from `data()`.
 */

#include "utils/test/Tester.h"
#include "Gpu/Math/Matrix.h"

using Gpu::Math::Matrix;

int main() {
    Tester tester("Gpu::Math::Matrix data() access");

    Matrix mat(3, 3);

    std::vector<double>& buffer = mat.data();
    buffer[0] = 1.0;
    buffer[4] = 2.5;
    buffer[8] = -3.75;

    tester.assertEqual(mat.at(0, 0), 1.0, "Direct data()[0] reflected in at(0,0)");
    tester.assertEqual(mat.at(1, 1), 2.5, "Direct data()[4] reflected in at(1,1)");
    tester.assertEqual(mat.at(2, 2), -3.75, "Direct data()[8] reflected in at(2,2)");

    const Matrix& constMat = mat;
    const std::vector<double>& constBuf = constMat.data();
    tester.assertEqual(constBuf[4], 2.5, "Const data() read confirms value");

    tester.pass();
}
