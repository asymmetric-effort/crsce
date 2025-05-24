// file: include/utils/test/Tester.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include "Gpu/Device/Interface.h"
#include "utils/test/ExitOnError.h"
#include "Gpu/Ipc/Result.h"
#include <exception>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

class Tester {
public:

    // Construct with a test prefix (e.g., "test/0100_Gpu_mock_init")
    explicit Tester(const std::string& prefix, ExitOnError onError=false);
    ~Tester();

    template<typename ExpectedExceptionClass, typename PayloadFunc>
    void expectException(PayloadFunc&& func);

    // assert<True|False> a condition; on failure, print message and terminate
    void assertTrue(bool condition, const std::string& message);
    void assertFalse(bool condition, const std::string& message);

    // assertNotNull passes only if ptr is not null.
    void assertNotNull(const void* ptr, const std::string& message);

    void assertNotNull(const std::unique_ptr<void>& ptr, const std::string& message);
    // void assertNotNull(const std::unique_ptr<Gpu::Interface>& ptr, const std::string& message);

    void assertNotNull(const std::shared_ptr<void>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<int>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<unsigned>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<float>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<double>& ptr, const std::string& message);
    void assertNotNull(const std::shared_ptr<char>& ptr, const std::string& message);

    void assertNotNull(const std::weak_ptr<void>& ptr, const std::string& message);

    // Assert two values are equal; on success counts as pass, on failure counts and logs
    void assertEqual(int a, int b, const std::string& message);
    void assertEqual(size_t a, size_t b, const std::string& message);
    void assertEqual(uint16_t a, uint16_t b, const std::string& message);
    void assertEqual(uint64_t a, uint64_t b, const std::string& message);
    void assertEqual(unsigned a, unsigned b, const std::string& message);
    void assertEqual(uint8_t a, uint8_t b, const std::string& message);
    void assertEqual(float a, float b, const std::string& message);
    void assertEqual(double a, double b, const std::string& message);
    void assertEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string& message);

    void assertNotEqual(int a, int b, const std::string& message);
    void assertNotEqual(size_t a, size_t b, const std::string& message);
    void assertNotEqual(uint16_t a, uint16_t b, const std::string& message);
    void assertNotEqual(uint64_t a, uint64_t b, const std::string& message);
    void assertNotEqual(unsigned a, unsigned b, const std::string& message);
    void assertNotEqual(char a, char b, const std::string& message);
    void assertNotEqual(float a, float b, const std::string& message);
    void assertNotEqual(double a, double b, const std::string& message);
    // mark failure
    void fail();
    void fail(const std::string& message);

    // mark pass
    void pass();
    void pass(const std::string& message);

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

template<typename ExpectedExceptionClass, typename PayloadFunc>
void Tester::expectException(PayloadFunc&& func) {
    try {
        func();
        fail("Expected exception of type " + std::string(typeid(ExpectedExceptionClass).name()) + " not thrown");
    } catch (const ExpectedExceptionClass&) {
        return; // expected
    } catch (const std::exception& e) {
        fail("Unexpected std::exception: " + std::string(e.what()));
    } catch (...) {
        fail("Unexpected non-standard exception in context");
    }
}
