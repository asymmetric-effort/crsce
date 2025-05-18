// file: include/utils/test/getFailCount.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

const int Tester::getFailCount(){
    return failScore;
}
