// file: test/0300_Gpu_Mock_UseThreads.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#define GPU_EMULATOR

#include "Gpu/Interface.h"
#include "utils/test/Tester.h"
#include <cstring>
#include <iostream>
#include <vector>

int main() {
    Tester tester("test/0300_Gpu_Mock_UseThreads");
    // Todo: test our ability to perform a simple parallel math operation on our Gpu/Emulator.
    // ToDo: Ensure that if we pass a current state we get our expected end state after Gpu/Emulator performs the math.
    return 0;
}
