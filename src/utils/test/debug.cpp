// file: src/utils/test/debug.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// debug: show a debug message
void Tester::debug(const std::string& msg){
    std::cerr << "[" << prefix << "] " << msg << std::endl;
}
