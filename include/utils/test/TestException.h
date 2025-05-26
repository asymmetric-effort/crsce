// file: include/utils/test/TestException.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#pragma once

#include <exception>
#include <string>

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
