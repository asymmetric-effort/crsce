/**
 * @file include/utils/test/TestException.h
 * @brief Declare the TestException class representing a test assertion failure.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

#include <exception>
#include <string>

/**
 * @name TestException
 * @class TestException
 * @brief An exception representing a test failure.
 */
class TestException final : public std::exception {
public:
    explicit TestException() = default;

    explicit TestException(std::string message) : message_(std::move(message)) {
    }

    const char *what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
