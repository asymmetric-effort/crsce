// file: src/utils/test/pass.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// increment pass score and terminate
void Tester::pass(){
    passScore++;
}

void Tester::pass(const std::string& message){
    debug(message);
    pass();
}
