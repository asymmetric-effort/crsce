// file: src/utils/test/fail.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// increment fail score and terminate
void Tester::fail(){
    failScore++;
    if (onError) {
        showStatistics();
        std::exit(EXIT_FAILURE);
    }
}

void Tester::fail(const std::string& msg){
    debug(msg);
    fail();
}
