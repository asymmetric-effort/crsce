/**
* @file src/CRSCE/CRSCE.serialize_output.cpp
 * @brief define a method which serializes the output of the cross sums and LHASH matrix
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/CRSCE.h"

void CRSCE::serialize_output(const LateralSumMatrix &LSM, const VerticalSumMatrix &VSM, const DiagonalSumMatrix &XSM,
                             const AntidiagonalSumMatrix &DSM, const LHashMatrix &LHASH) {

    // Serialize all five matrices for this block
    LHASH.serialize(outputStream);
    LSM.serialize(outputStream);
    VSM.serialize(outputStream);
    XSM.serialize(outputStream);
    DSM.serialize(outputStream);
    outputStream.flush();

}
