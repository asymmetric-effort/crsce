// file: include/utils/test/Tester.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class Tester {
public:
    // Construct with a test prefix (e.g., "test/0100_Gpu_mock_init")
    Tester(const std::string& prefix);
    ~Tester();

    // Assert a condition; on failure, print message and terminate
    void assertTrue(bool condition, const std::string& message);

    void fail();
    void pass();

private:
    std::string prefix;
    unsigned int pass_score=0;
    unsigned int fail_score=0;
};
