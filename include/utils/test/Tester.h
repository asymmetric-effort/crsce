/**
 * @file include/utils/test/Tester.h
 * @brief Declare a tester class to manage unit and integration tests.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "utils/test/ExitOnError.h"
#include <exception>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <cstdint>   // for UINT64_MAX

class Tester {
public:
    /**
     * @name constructor
     * @brief prints "Tester Initialized" message
     * @param prefix
     * @param onError
     */
    explicit Tester(const std::string &prefix, ExitOnError onError = false);

    explicit Tester(const Tester &) = delete;

    explicit Tester(Tester &&) = delete;

    Tester &operator=(const Tester &) = delete;

    Tester &operator=(Tester &&) noexcept = delete;

    /**
     * @name destructor
     * @brief show test statistics and if there were errors, terminate with non-zero exit code.
     */
    ~Tester();

    /**
     * @name expectException
     * @brief Executes a given lambda function and expects that it will throw the given exception.
     * @tparam ExpectedExceptionClass
     * @tparam PayloadFunc
     * @param func
     */
    template<typename ExpectedExceptionClass, typename PayloadFunc>
    void expectException(PayloadFunc &&func);

    /**
     * @name assertTrue
     * @brief assert that the input condition must be true
     * @param condition bool
     * @param message std::string
     */
    void assertTrue(bool condition, const std::string &message);

    /**
     * @name assertFalse
     * @brief assert that the input condition must be false
     * @param condition bool
     * @param message std::string
     */
    void assertFalse(bool condition, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs Common::double
     * @param rhs Common::double
     * @param message std::string
     */
    void assertEqual(double lhs, double rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs float
     * @param rhs float
     * @param message std::string
     */
    void assertEqual(float lhs, float rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief assert that a != b.
     * @param lhs char
     * @param rhs char
     * @param message std::string
     */
    void assertEqual(const int lhs, const int rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs size_t
     * @param rhs size_t
     * @param message std::string
     */
    void assertEqual(const size_t lhs, const size_t rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief assert that a != b.
     * @param lhs uint8_t
     * @param rhs uint8_t
     * @param message std::string
     */
    void assertEqual(const uint8_t lhs, const uint8_t rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs uint16_t
     * @param rhs uint16_t
     * @param message std::string
     */
    void assertEqual(const uint16_t lhs, const uint16_t rhs, const std::string &message);

#if SIZE_MAX != UINT64_MAX
    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs uint64_t
     * @param rhs uint64_t
     * @param message std::string
     */
    void assertEqual(uint64_t lhs, uint64_t rhs, const std::string &message);
#endif

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs uint32_t
     * @param rhs uint32_t
     * @param message std::string
     */
    void assertEqual(const uint32_t lhs, const uint32_t rhs, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs std::string
     * @param rhs std::string
     * @param message std::string
     */
    void assertEqual(const std::string& lhs, const std::string& rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs double
     * @param rhs double
     * @param message std::string
     */
    void assertNotEqual(double lhs, const double rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs float
     * @param rhs float
     * @param message std::string
     */
    void assertNotEqual(const float lhs, const float rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs int
     * @param rhs int
     * @param message std::string
     */
    void assertNotEqual(const int lhs, const int rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs size_t
     * @param rhs size_t
     * @param message std::string
     */
    void assertNotEqual(const size_t lhs, const size_t rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief assert that a != b.
     * @param lhs uint8_t
     * @param rhs uint8_t
     * @param message std::string
     */
    void assertNotEqual(const uint8_t lhs, const uint8_t rhs, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs uint16_t
     * @param rhs uint16_t
     * @param message std::string
     */
    void assertNotEqual(const uint16_t lhs, const uint16_t rhs, const std::string &message);

#if SIZE_MAX != UINT64_MAX
    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs uint64_t
     * @param rhs uint64_t
     * @param message std::string
     */
    void assertNotEqual(uint64_t lhs, uint64_t rhs, const std::string &message);
#endif

    /**
     * @name assertNotEqual
     * @brief asserts that lhs should equal rhs
     * @param lhs unsigned int
     * @param rhs unsigned int
     * @param message std::string
     */
    void assertNotEqual(const unsigned lhs, const unsigned rhs, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr Gpu::Ipc::Result
     * @param message std::string
     */
    void assertNotNull(const void *ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr std::unique_ptr<void>
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<void> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<int> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<unsigned> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<float> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<double> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::unique_ptr<char> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr std::shared_ptr<void>
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<void> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr std::shared_ptr<int>
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<int> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<unsigned> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr std::shared_ptr<float>
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<float> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr std::shared_ptr<double>
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<double> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that ptr is not null
     * @param ptr void*
     * @param message std::string
     */
    void assertNotNull(const std::shared_ptr<char> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that lhs should equal rhs
     * @param ptr std::weak_ptr<void>
     * @param message std::string
     */
    void assertNotNull(const std::weak_ptr<void> &ptr, const std::string &message);

    /**
     * @name fail
     * @brief update stats and throw a message exception.  OnError (true) terminates execution.
     * @throw TestException
     */
    void fail();

    /**
     * @name fail
     * @brief record message, update stats and throw a message exception.  OnError (true) terminates execution.
     * @param message std::string
     * @throw TestException
     */
    void fail(const std::string &message);

    /**
     * @name recoverFail()
     * @brief expectedException will recover from a previous fail by deducting the fail.
     */
    void recoverFail() { if (failScore > 0)failScore--; };

    /**
     * @name pass
     * @brief increment the passing score
     */
    void pass();

    /**
     * @name pass
     * @brief increment the passing score
     * @param message std::string
     */
    void pass(const std::string &message);

    /**
     * @name skip
     * @param msg @name skip
     * @brief increment skip score and terminate
     * @param message std::string
     */
    void skip(const std::string &message);

    /**
     * @name getFailCount
     * @brief return the number of failed checks
     * @return int
     */
    int getFailCount() const { return failScore; }

    /**
     * @name getPassCount
     * @brief return the number of passing checks
     * @return int
     */
    int getPassCount() const { return passScore; }
    /**
     * @name getSkipCount
     * @brief return the number of skipped checks
     * @return int
     */
    int getSkipCount() const { return skipScore; }

    /**
     * @brief Set a maximum duration (in seconds) for this test.
     * If the deadline elapses before the test completes, the process exits.
     * @param t Time in seconds until forced termination (default 60s).
     * @param exit_code_on_deadline
     */
    void deadline(unsigned t = 60, int exit_code_on_deadline = EXIT_FAILURE);

    /**
     * @name debug
     * @brief print debug message
     * @param message std::string
     */
    void debug(const std::string &msg) const;

private:
    /**
    * @name showStatistics
    * @brief print the test statistics (pass, fail, skip)
    */
    void showStatistics() const;

    std::string prefix;
    unsigned int passScore = 0;
    unsigned int failScore = 0;
    unsigned int skipScore = 0;
    ExitOnError onError;
};

/**
 * @name expectException
 * @brief perform test function and pass if expected exception is thrown or fail if not.
 * @tparam ExpectedExceptionClass
 * @tparam PayloadFunc
 * @param func
 */
template<typename ExpectedExceptionClass, typename PayloadFunc>
void Tester::expectException(PayloadFunc &&func) {
    try {
        func();
        fail("Expected exception of type " + std::string(typeid(ExpectedExceptionClass).name()) + " not thrown");
    } catch (const ExpectedExceptionClass) {
        recoverFail();
        pass(std::format("expected exception ({}) was thrown", std::string(typeid(ExpectedExceptionClass).name())));
    } catch (const std::exception &e) {
        fail("Unexpected std::exception: " + std::string(e.what()));
    } catch (...) {
        fail("Unexpected non-standard exception in context");
    }
}
