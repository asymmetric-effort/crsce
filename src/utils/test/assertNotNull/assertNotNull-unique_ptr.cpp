/**
 * @file include/utils/test/assertNotNull/assertNotNull-DeviceInterface.h
 * @brief Declares an assertion which expects inequality.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#include "utils/test/Tester.h"

/**
 * @name assertNotNull
 * @brief Asserts that ptr is not a null pointer.
 * @param ptr <Gpu::Device::Interface>
 * @param message std::string
 */
void Tester::assertNotNull(const std::unique_ptr<Gpu::Device::Interface> &ptr, const std::string &message) {
    if (ptr.get() == nullptr)
        fail(message);
    else
        pass();
}
