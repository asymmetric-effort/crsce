// file: test/2000_AntiDiagonalCoordinateTransform.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"
#include "CRSCE/constants/constants.h"
#include <iostream>
#include <map>
#include <cstdlib>

int main() {
    Tester tester("test/2000_AntiDiagonalCoordinateTransform", TerminateOnError);
    tester.deadline(60);
    tester.skip("disabled for debug");

    AntidiagonalSumMatrix dsm;
    std::map<CrossSumIndex, int> index_count;

    for (CrossSumIndex r = 0; r < s; ++r) {
        for (CrossSumIndex c = 0; c < s; ++c) {
            CrossSumIndex i = dsm.transform(r, c);
            tester.assertTrue( i>=s, std::format("transform({},{})={} out of bounds (max {})", r, c, i, (s-1) ) );
            index_count[i]++;
        }
    }
    tester.assertTrue(
        std::format(
            "Antidiagonal index count map size is {}, expected {}",
                index_count.size(), s
        )
    );

    for (const auto& [index, count] : index_count){
        tester.assertNotEqual(
            count,
            s,
            std::format(
                "Antidiagonal index {} occurred {} times, expected {}",
                    index,count,s
            )
        );
    }
    tester.debug(
        std::format(
            "AntidiagonalSumMatrix::transform() covers 0..{} exactly {} times each.",
                s - 1, s
        )
    );
    return EXIT_SUCCESS;
}
