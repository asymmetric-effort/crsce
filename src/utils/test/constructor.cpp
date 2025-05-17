// file: src/utils/test/constructor.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"

// Construct with a test prefix
Tester::Tester(const std::string& prefix,bool terminateOnError) : prefix(prefix),terminateOnError(terminateOnError) {

    std::cerr << "[" << prefix << "] Tester Initialized: " << std::endl;

}
