// file: test/0003\_tester\_pointer\_overloads.cpp
// (c) 2025 Asymmetric Effort, LLC. [scaldwell@asymmetric-effort.com](mailto:scaldwell@asymmetric-effort.com)

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include "Gpu/Device/Interface.h"
#include <memory>
#include <new>
#include <cstdint>

int main() {
Tester tester("0003_tester_pointer_overloads.cpp");

// ---- raw pointer tests ----
int *raw_ptr = new int(42);
tester.assertNotNull(raw_ptr, "raw pointer should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(static_cast<int*>(nullptr), "raw pointer should not be null"); });
delete raw_ptr;

// ---- unique_ptr<void> tests ----
std::unique_ptr<void> upv(operator new(1));
tester.assertNotNull(upv, "unique_ptr<void> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<void>(), "unique_ptr<void> should not be null"); });

// ---- unique_ptr<int> tests ----
auto upi = std::make_unique<int>(7);
tester.assertNotNull(upi, "unique_ptr<int> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<int>(), "unique_ptr<int> should not be null"); });

// ---- unique_ptr<unsigned> tests ----
auto upu = std::make_unique<unsigned>(123u);
tester.assertNotNull(upu, "unique_ptr<unsigned> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<unsigned>(), "unique_ptr<unsigned> should not be null"); });

// ---- unique_ptr<float> tests ----
auto upf = std::make_unique<float>(3.14f);
tester.assertNotNull(upf, "unique_ptr<float> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<float>(), "unique_ptr<float> should not be null"); });

// ---- unique_ptr<double> tests ----
auto upd = std::make_unique<double>(2.718);
tester.assertNotNull(upd, "unique_ptr<double> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<double>(), "unique_ptr<double> should not be null"); });

// ---- unique_ptr<char> tests ----
auto upc = std::make_unique<char>('x');
tester.assertNotNull(upc, "unique_ptr<char> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<char>(), "unique_ptr<char> should not be null"); });

// ---- shared_ptr<void> / weak_ptr<void> tests ----
std::shared_ptr<void> spv(operator new(1), [](void* p){ ::operator delete(p); });
std::weak_ptr<void> wpv(spv);
tester.assertNotNull(wpv, "weak_ptr<void> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::weak_ptr<void>() , "weak_ptr<void> should not be null"); });

// ---- shared_ptr<int> tests ----
std::shared_ptr<int> spi = std::make_shared<int>(99);
tester.assertNotNull(spi, "shared_ptr<int> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::shared_ptr<int>() , "shared_ptr<int> should not be null"); });

// ---- shared_ptr<unsigned> tests ----
std::shared_ptr<unsigned> spu = std::make_shared<unsigned>(456u);
tester.assertNotNull(spu, "shared_ptr<unsigned> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::shared_ptr<unsigned>() , "shared_ptr<unsigned> should not be null"); });

// ---- shared_ptr<float> tests ----
std::shared_ptr<float> spf = std::make_shared<float>(1.23f);
tester.assertNotNull(spf, "shared_ptr<float> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::shared_ptr<float>() , "shared_ptr<float> should not be null"); });

// ---- shared_ptr<double> tests ----
std::shared_ptr<double> spd = std::make_shared<double>(4.56);
tester.assertNotNull(spd, "shared_ptr<double> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::shared_ptr<double>() , "shared_ptr<double> should not be null"); });

// ---- shared_ptr<char> tests ----
std::shared_ptr<char> spc = std::make_shared<char>('z');
tester.assertNotNull(spc, "shared_ptr<char> should not be null");
tester.expectException<TestException>([&] { tester.assertNotNull(std::shared_ptr<char>() , "shared_ptr<char> should not be null"); });

// ---- unique_ptr<Gpu::Device::Interface> tests ----
tester.expectException<TestException>([&] { tester.assertNotNull(std::unique_ptr<Gpu::Device::Interface>(), "unique_ptr<Interface> should not be null"); });

return EXIT_SUCCESS;

}
