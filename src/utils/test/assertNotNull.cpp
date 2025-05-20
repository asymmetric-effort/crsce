// file: src/utils/test/assertNotNull.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
#include "utils/test/Tester.h"

// Overload for raw pointers
void Tester::assertNotNull(const void* ptr, const std::string& message) {
    if (ptr==nullptr)
        fail(std::format("Null pointer assertion failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}

// unique_ptr<void> overload
void Tester::assertNotNull(const std::unique_ptr<void>& ptr, const std::string& message) {
    if (ptr.get()==nullptr)
        fail(std::format("assertNotNull Failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}

// unique_ptr<Gpu::Interface> overload delegates to raw pointer
void Tester::assertNotNull(const std::unique_ptr<Gpu::Interface>& ptr, const std::string& message) {
    assertNotNull(ptr.get(), message);
}

// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<void>& ptr, const std::string& message) {
    if (ptr.get()==nullptr)
        fail(std::format("assertNotNull Failed: {}", message));
    else
        pass(std::format("ok: {}", message));
}


// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<int>& ptr, const std::string& message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}


// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<unsigned>& ptr, const std::string& message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}


// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<float>& ptr, const std::string& message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}

// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<double>& ptr, const std::string& message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
}

// Overload for shared_ptr convertible to void
void Tester::assertNotNull(const std::shared_ptr<char>& ptr, const std::string& message) {
    assertNotNull(std::static_pointer_cast<void>(ptr), message);
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
