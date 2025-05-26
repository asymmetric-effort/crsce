// file: src/utils/test/assertNotEqual.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(int a, int b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(size_t a, size_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(uint16_t a, uint16_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}


// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(uint64_t a, uint64_t b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(unsigned int a, unsigned int b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(char a, char b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(float a, float b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(double a, double b, const std::string& message) {
    if (a != b)
        pass(std::format("ok: {}", message));
    else
        fail(std::format("assertNotEqual failed({} != {}): {}", a, b, message));
}

void Tester::assertNotEqual(const Common::Buffer8& a, const Common::Buffer8& b, const std::string& msg) {
    if (a.size() != b.size()) {
        std::ostringstream oss;
        oss << msg << " [size mismatch: " << a.size() << " != " << b.size() << "]";
        fail(oss.str());
    }

    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            std::ostringstream oss;
            oss << msg << " [mismatch at byte " << i << ": "
                << std::hex << static_cast<int>(a[i])
                << " != " << static_cast<int>(b[i]) << "]";
            fail(oss.str());
        }
    }
}

void Tester::assertNotEqual(const Common::Buffer64& a, const Common::Buffer64& b, const std::string& msg) {
    if (a.size() != b.size()) {
        std::ostringstream oss;
        oss << msg << " [size mismatch: " << a.size() << " != " << b.size() << "]";
        fail(oss.str());
    }

    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            std::ostringstream oss;
            oss << msg << " [mismatch at byte " << i << ": "
                << std::hex << static_cast<int>(a[i])
                << " != " << static_cast<int>(b[i]) << "]";
            fail(oss.str());
        }
    }
}

void Tester::assertNotEqual(const Gpu::Math::Matrix &a, const Gpu::Math::Matrix &b, const std::string &msg) {
    if (a.rows() != b.rows() || a.cols() != b.cols()) {
        std::ostringstream oss;
        oss << msg << " [shape mismatch: " << a.rows() << "x" << a.cols()
            << " != " << b.rows() << "x" << b.cols() << "]";
        fail(oss.str());
    }

    for (std::size_t r = 0; r < a.rows(); ++r) {
        for (std::size_t c = 0; c < a.cols(); ++c) {
            if (a.at(r, c) != b.at(r, c)) {
                std::ostringstream oss;
                oss << msg << " [mismatch at (" << r << "," << c << "): "
                    << a.at(r, c) << " != " << b.at(r, c) << "]";
                fail(oss.str());
            }
        }
    }
}
