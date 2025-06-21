/**
 * @file include/utils/test/Tester.h
 * @brief Declare a tester class to manage unit and integration tests.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include "Gpu/Device/Interface.h"
#include "utils/test/ExitOnError.h"
#include "Gpu/Math/Matrix.h"
#include "Gpu/Ipc/Result.h"
#include <exception>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <cstdint>   // for UINT64_MAX
#include <cstddef>   // for SIZE_MAX

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
     * @brief asserts that a should equal b
     * @param a Common::Buffer8&
     * @param b Common::Buffer8&
     * @param message std::string&
     */
    void assertEqual(const Common::Buffer8 &a, const Common::Buffer8 &b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a Common::Buffer64&
     * @param b Common::Buffer64&
     * @param message std::string&
     */
    void assertEqual(const Common::Buffer64 &a, const Common::Buffer64 &b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a Common::double
     * @param b Common::double
     * @param message std::string
     */
    void assertEqual(double a, double b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a float
     * @param b float
     * @param message std::string
     */
    void assertEqual(float a, float b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a Gpu::Ipc::Result
     * @param b Gpu::Ipc::Result
     * @param message std::string&
     */
    void assertEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a Gpu::Math::Matrix&
     * @param b Gpu::Math::Matrix&
     * @param message std::string&
     */
    void assertEqual(const Gpu::Math::Matrix &a, const Gpu::Math::Matrix &b, const std::string &msg);

    /**
     * @name assertEqual
     * @brief assert that a != b.
     * @param a char
     * @param b char
     * @param message std::string
     */
    void assertEqual(int a, int b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a size_t
     * @param b size_t
     * @param message std::string
     */
    void assertEqual(size_t a, size_t b, const std::string &message);

    /**
     * @name assertEqual
     * @brief assert that a != b.
     * @param a uint8_t
     * @param b uint8_t
     * @param message std::string
     */
    void assertEqual(uint8_t a, uint8_t b, const std::string &message);

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a uint16_t
     * @param b uint16_t
     * @param message std::string
     */
    void assertEqual(uint16_t a, uint16_t b, const std::string &message);

#if SIZE_MAX != UINT64_MAX
    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a uint64_t
     * @param b uint64_t
     * @param message std::string
     */
    void assertEqual(uint64_t a, uint64_t b, const std::string &message);
#endif

    /**
     * @name assertEqual
     * @brief asserts that a should equal b
     * @param a unsigned int
     * @param b unsigned int
     * @param message std::string
     */
    void assertEqual(unsigned a, unsigned b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief Assert that two Common::Buffer8 objects are not equal.
     * @param a First buffer to compare.
     * @param b Second buffer to compare.
     * @param message Message to display on assertion outcome.
     */
    void assertNotEqual(const Common::Buffer8 &a, const Common::Buffer8 &b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief Assert that two Common::Buffer64 objects are not equal.
     * @param a First buffer to compare.
     * @param b Second buffer to compare.
     * @param message Message to display on assertion outcome.
     */
    void assertNotEqual(const Common::Buffer64 &a, const Common::Buffer64 &b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a double
     * @param b double
     * @param message std::string
     */
    void assertNotEqual(double a, const double b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a float
     * @param b float
     * @param message std::string
     */
    void assertNotEqual(float a, const float b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a int
     * @param b int
     * @param message std::string
     */
    void assertNotEqual(Gpu::Ipc::Result a, Gpu::Ipc::Result b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief Assert that two matrices are not equal within a given tolerance.
     * @param a First Gpu::Math::Matrix to compare.
     * @param b Second Gpu::Math::Matrix to compare.
     * @param message Message to display on assertion outcome.
     */
    void assertNotEqual(const Gpu::Math::Matrix &a, const Gpu::Math::Matrix &b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a int
     * @param b int
     * @param message std::string
     */
    void assertNotEqual(const int a, const int b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a size_t
     * @param b size_t
     * @param message std::string
     */
    void assertNotEqual(size_t a, size_t b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief assert that a != b.
     * @param a uint8_t
     * @param b uint8_t
     * @param message std::string
     */
    void assertNotEqual(uint8_t a, uint8_t b, const std::string &message);

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a uint16_t
     * @param b uint16_t
     * @param message std::string
     */
    void assertNotEqual(uint16_t a, uint16_t b, const std::string &message);

#if SIZE_MAX != UINT64_MAX
    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a uint64_t
     * @param b uint64_t
     * @param message std::string
     */
    void assertNotEqual(uint64_t a, uint64_t b, const std::string &message);
#endif

    /**
     * @name assertNotEqual
     * @brief asserts that a should equal b
     * @param a unsigned int
     * @param b unsigned int
     * @param message std::string
     */
    void assertNotEqual(unsigned a, unsigned b, const std::string &message);

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

    void assertNotNull(const std::unique_ptr<Gpu::Device::Interface> &ptr, const std::string &message);

    /**
     * @name assertNotNull
     * @brief asserts that a should equal b
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
    void showStatistics();

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
    } catch (const ExpectedExceptionClass &e) {
        recoverFail();
        pass(std::format("expected exception ({}) was thrown", std::string(typeid(ExpectedExceptionClass).name())));
    } catch (const std::exception &e) {
        fail("Unexpected std::exception: " + std::string(e.what()));
    } catch (...) {
        fail("Unexpected non-standard exception in context");
    }
}
