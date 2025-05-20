// file: src/utils/test/assertEqual.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(int a, int b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(size_t a, size_t b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(uint16_t a, uint16_t b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(uint64_t a, uint64_t b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(unsigned int a, unsigned int b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(char a, char b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(float a, float b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertEqual(double a, double b, const std::string& message) {
    if (a == b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertEqual failed({} != {}): {}", a, b, message));
}
