/**
* @file test/0050_common_AbstractPtr.cpp
 * @brief Sanity check for Common::AbstractPtr size and max value.
 */

#include "utils/test/Tester.h"     // your test harness :contentReference[oaicite:0]{index=0}
#include "Common/AbstractPtr.h"    // defines Common::AbstractPtr :contentReference[oaicite:1]{index=1}

#include <climits>    // for CHAR_BIT
#include <limits>     // for std::numeric_limits
#include <cstdlib>    // for EXIT_SUCCESS/EXIT_FAILURE

int main() {
    // point the harness at this file; throw on first failure is fine here
    Tester tester("0050_common_AbstractPtr.cpp", ThrowExceptionOnError);

    // -- bit-width must be exactly 64 bits
    tester.assertTrue(
        sizeof(Common::AbstractPtr) * CHAR_BIT == 64,
        "Common::AbstractPtr must be exactly 64 bits wide"
    );

    // -- max value must be all-ones (i.e. ~0)
    tester.assertTrue(
        std::numeric_limits<Common::AbstractPtr>::max()
          == ~static_cast<Common::AbstractPtr>(0),
        "Common::AbstractPtr max value must be all bits set (~0)"
    );

    // print summary and return 0 if everything passed, 1 otherwise
    tester.pass();
    return 0;
}
