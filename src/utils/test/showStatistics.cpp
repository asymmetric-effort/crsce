// file: src/utils/test/showStatistics.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

void Tester::showStatistics(){
    std::cerr <<
        "[" << prefix << "] Tester tear-down: " << std::endl
        << " Pass: " << passScore << std::endl
        << " Fail: " << failScore << std::endl
        << "Total: " << (passScore + failScore) << std::endl
        << std::endl;
}
