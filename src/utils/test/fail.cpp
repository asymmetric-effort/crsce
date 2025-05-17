// file: src/utils/test/fail.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// increment fail score and terminate
void Tester::fail(){
    failScore++;
    std::exit(EXIT_FAILURE);
}
