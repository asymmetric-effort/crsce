// file: src/utils/test/assertNotEqual.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(int a, int b, const std::string& message) {
    if (a != b) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] assertNotEqual failed: " << message
                  << " (" << a << " != " << b << ")" << std::endl;
        fail();
    }
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(unsigned int a, unsigned int b, const std::string& message) {
    if (a != b) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] assertNotEqual failed: " << message
                  << " (" << a << " != " << b << ")" << std::endl;
        fail();
    }
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(char a, char b, const std::string& message) {
    if (a != b) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] assertNotEqual failed: " << message
                  << " ('" << a << "' != '" << b << "')" << std::endl;
        fail();
    }
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(float a, float b, const std::string& message) {
    if (a != b) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] assertNotEqual failed: " << message
                  << " (" << a << " != " << b << ")" << std::endl;
        fail();
    }
}

// Assert two values are equal; on success counts as pass, on failure counts and logs
void Tester::assertNotEqual(double a, double b, const std::string& message) {
    if (a != b) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] assertNotEqual failed: " << message
                  << " (" << a << " != " << b << ")" << std::endl;
        fail();
    }
}
