// file: src/CRSCE/CRSCE.deserialize_input.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CRSCE.h"

#include "CRSCE/LHashMatrix.h"
#include "CRSCE/CrossSum/LateralSumMatrix/LateralSumMatrix.h"
#include "CRSCE/CrossSum/VerticalSumMatrix/VerticalSumMatrix.h"
#include "CRSCE/CrossSum/DiagonalSumMatrix/DiagonalSumMatrix.h"
#include "CRSCE/CrossSum/AntidiagonalSumMatrix/AntidiagonalSumMatrix.h"

void CRSCE::deserialize_input(const LateralSumMatrix& LSM,
                              const VerticalSumMatrix& VSM,
                              const DiagonalSumMatrix& XSM,
                              const AntidiagonalSumMatrix& DSM,
                              const LHashMatrix& LHASH) {
    LHASH.deserialize(inputStream);
    LSM.deserialize(inputStream);
    VSM.deserialize(inputStream);
    XSM.deserialize(inputStream);
    DSM.deserialize(inputStream);
}