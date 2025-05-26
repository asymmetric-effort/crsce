// file: src/utils/test/skip.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// increment skip score and terminate
void Tester::skip(const std::string& msg){
    std::cerr << "[" << prefix << "] Tester::skip() " << msg << std::endl;
    skipScore++;
    showStatistics();
    std::exit(EXIT_SUCCESS);
}
