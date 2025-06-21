/**
 * @file 0003_tester_pointer_overloads.cpp
 * @brief Verifies Tester::assertNotNull overloads for raw pointers, unique_ptr, shared_ptr, and weak_ptr (including Gpu::Device::Interface).
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "utils/test/TestException.h"
#include "Gpu/Device/Interface.h"
#include <memory>
#include <cstdlib>

int main() {
    Tester tester("0003_tester_pointer_overloads.cpp");

    // ---- raw void* pointer tests ----
    void* vp = operator new(1);
    tester.assertNotNull(vp, "raw void* should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(static_cast<void*>(nullptr), "raw void* should not be null"); }
    );
    operator delete(vp);

    // ---- raw int* pointer tests ----
    // ReSharper disable once CppUseAuto
    // ReSharper disable once CppLocalVariableMayBeConst
    int* raw = new int(42);
    tester.assertNotNull(raw, "raw int* should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(static_cast<int*>(nullptr), "raw int* should not be null"); }
    );
    delete raw;

    // ---- unique_ptr<int> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto upi = std::make_unique<int>(7);
    tester.assertNotNull(upi, "unique_ptr<int> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<int>(), "unique_ptr<int> should not be null"); }
    );

    // ---- unique_ptr<unsigned> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto upu = std::make_unique<unsigned>(123u);
    tester.assertNotNull(upu, "unique_ptr<unsigned> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<unsigned>(), "unique_ptr<unsigned> should not be null"); }
    );

    // ---- unique_ptr<float> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto upf = std::make_unique<float>(3.14f);
    tester.assertNotNull(upf, "unique_ptr<float> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<float>(), "unique_ptr<float> should not be null"); }
    );

    // ---- unique_ptr<double> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto upd = std::make_unique<double>(2.718);
    tester.assertNotNull(upd, "unique_ptr<double> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<double>(), "unique_ptr<double> should not be null"); }
    );

    // ---- unique_ptr<char> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto upc = std::make_unique<char>('x');
    tester.assertNotNull(upc, "unique_ptr<char> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<char>(), "unique_ptr<char> should not be null"); }
    );

    // ---- shared_ptr<void> / weak_ptr<void> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    std::shared_ptr<void> spv(operator new(1), [](void* p){ ::operator delete(p); });
    std::weak_ptr<void> wpv(spv);
    tester.assertNotNull(wpv, "weak_ptr<void> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::weak_ptr<void>(), "weak_ptr<void> should not be null"); }
    );

    // ---- shared_ptr<int> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto spi = std::make_shared<int>(99);
    tester.assertNotNull(spi, "shared_ptr<int> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::shared_ptr<int>(), "shared_ptr<int> should not be null"); }
    );

    // ---- shared_ptr<unsigned> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto spu = std::make_shared<unsigned>(456u);
    tester.assertNotNull(spu, "shared_ptr<unsigned> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::shared_ptr<unsigned>(), "shared_ptr<unsigned> should not be null"); }
    );

    // ---- shared_ptr<float> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto spf = std::make_shared<float>(1.23f);
    tester.assertNotNull(spf, "shared_ptr<float> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::shared_ptr<float>(), "shared_ptr<float> should not be null"); }
    );

    // ---- shared_ptr<double> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto spd = std::make_shared<double>(4.56);
    tester.assertNotNull(spd, "shared_ptr<double> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::shared_ptr<double>(), "shared_ptr<double> should not be null"); }
    );

    // ---- shared_ptr<char> tests ----
    // ReSharper disable once CppLocalVariableMayBeConst
    auto spc = std::make_shared<char>('z');
    tester.assertNotNull(spc, "shared_ptr<char> should not be null");
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::shared_ptr<char>(), "shared_ptr<char> should not be null"); }
    );

    // ---- unique_ptr<Gpu::Device::Interface> tests ----
    tester.expectException<TestException>(
        [&] { tester.assertNotNull(std::unique_ptr<Gpu::Device::Interface>(), "unique_ptr<Interface> should not be null"); }
    );

    return tester.getFailCount()>0?1:EXIT_SUCCESS;
}
