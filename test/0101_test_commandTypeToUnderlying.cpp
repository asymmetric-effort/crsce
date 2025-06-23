/**
* @file 0101_test_commandTypeToUnderlying.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "utils/to_underlying.h"
#include <unistd.h>
#include <cstdlib>
#include <format>
#include <map>
#include <typeinfo>

int main()
{
    Tester tester("0101_test_commandTypeToUnderlying.cpp");
    using enum Gpu::Ipc::CommandType;
    const std::map<Gpu::Ipc::CommandType, uint32_t> commands = {
        {Init, 0x00},
        {Alloc, 0x01},
        {Free, 0x02},
        {Write, 0x03},
        {Read, 0x04},
        {RegisterKernel, 0x05},
        {LaunchTask, 0x06},
        {Reset, 0x07},
        {Shutdown, 0x08},
    };
    for (auto [lhs, rhs] : commands)
    {
        auto const v_lhs = std::to_underlying(lhs);
        auto const v_rhs = rhs;

        auto const t_lhs = typeid(decltype(v_lhs)).hash_code();
        auto const t_rhs = typeid(decltype(v_rhs)).hash_code();

        tester.assertEqual(
            v_lhs,
            v_rhs,
            std::format("match type (lhs:{},rhs:{})",
                        std::__to_underlying(lhs),
                        rhs));

        tester.assertEqual(
            t_lhs,
            t_rhs,
            std::format("expected type match on v_lhs:{} t_lhs:{}, t_rhs:{}",
                        v_lhs, t_lhs, t_rhs));
    }

    tester.pass();
    return EXIT_SUCCESS;
}
