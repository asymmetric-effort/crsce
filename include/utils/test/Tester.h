// file: include/utils/test/Tester.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Device/Interface.h"
#include "utils/test/ExitOnError.h"
#include <cstdlib>
#include <iostream>
#include <string>

class Tester {
public:

    // Construct with a test prefix (e.g., "test/0100_Gpu_mock_init")
    Tester(const std::string& prefix, ExitOnError onError=false);
    ~Tester();

    // assertTrue a condition; on failure, print message and terminate
    void assertTrue(bool condition, const std::string& message);

    // assertNotNull passes only if ptr is not null.
    void assertNotNull(const void* ptr, const std::string& message);

    void assertNotNull(const std::unique_ptr<void>& ptr, const std::string& message);
    void assertNotNull(const std::unique_ptr<Gpu::Interface>& ptr, const std::string& message);

    void assertNotNull(const std::shared_ptr<void>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<int>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<unsigned>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<float>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<double>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<char>& ptr, const std::string& message);

    void assertNotNull(const std::weak_ptr<void>& ptr, const std::string& message);


    // Assert two values are equal; on success counts as pass, on failure counts and logs
    void assertEqual(int a, int b, const std::string& message);
    void assertEqual(unsigned a, unsigned b, const std::string& message);
    void assertEqual(char a, char b, const std::string& message);
    void assertEqual(float a, float b, const std::string& message);
    void assertEqual(double a, double b, const std::string& message);

    // mark failure
    void fail();

    // mark pass
    void pass();

    // skip test - terminates the test without error
    void skip(const std::string& msg);

    // getters...
    const int getSkipCount();
    const int getPassCount();
    const int getFailCount();

    /**
     * @brief Set a maximum duration (in seconds) for this test.
     * If the deadline elapses before the test completes, the process exits.
     * @param t Time in seconds until forced termination (default 60s).
     */
    void deadline(unsigned t = 60);

    // debug: show a debug message
    void debug(const std::string& msg);

private:

    void showStatistics();

    std::string prefix;
    unsigned int passScore=0;
    unsigned int failScore=0;
    unsigned int skipScore=0;
    ExitOnError onError;
};
