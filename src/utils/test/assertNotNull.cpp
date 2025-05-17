// file: src/utils/test/assertNotNull.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Overload for raw pointers
void Tester::assertNotNull(const void* ptr, const std::string& message) {
    if (ptr) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] Null pointer assertion failed: " << message << std::endl;
        fail();
    }
}

// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<void>& ptr, const std::string& message) {
    if (ptr.get()) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] Null shared_ptr assertion failed: " << message << std::endl;
        fail();
    }
}

// Overload for std::weak_ptr via lock
void Tester::assertNotNull(const std::weak_ptr<void>& ptr, const std::string& message) {
    if (auto sp = ptr.lock()) {
        pass();
    } else {
        std::cerr << '[' << prefix << "] Null weak_ptr assertion failed: " << message << std::endl;
        fail();
    }
}
