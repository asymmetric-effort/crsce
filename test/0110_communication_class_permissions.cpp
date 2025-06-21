/**
* @file 0110_communication_class_permissions.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Handles.h"
#include <unistd.h>
#include <cstdlib>
#include <format>
#include <map>
#include "utils/to_underlying.h"

int main() {
    using Gpu::Ipc::Communications;
    using enum Gpu::Ipc::CommandType;
    Tester tester("0110_communication_class_permissions.cpp");
    tester.deadline(240);

    tester.debug("create the bidirectional pipes");
    Gpu::Ipc::Handles toChild;
    Gpu::Ipc::Handles fromChild;

    tester.debug("setup communications channel");
    const Communications parent(toChild, fromChild, true);
    const Communications child(toChild, fromChild, false);

    tester.debug("examine state");
    tester.assertTrue(parent.validateParentAccess(),"parent access failed");
    tester.assertFalse(parent.validateChildAccess(),"child access should fail");

    tester.assertTrue(child.validateChildAccess(),"child access failed");
    tester.assertFalse(child.validateParentAccess(),"parent access should fail");

    tester.pass();
    return EXIT_SUCCESS;
}
