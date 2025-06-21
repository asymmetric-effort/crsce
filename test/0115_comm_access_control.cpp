/**
 * @file 0115_comm_access_control.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

/**
 * @file 0115_comm_access_control.cpp
 * @brief Validate that Gpu::Ipc::Communications correctly enforces parent/child access roles.
 *
 * This test checks that:
 *   - `validateParentAccess()` returns true only for parent
 *   - `validateChildAccess()` returns true only for child
 *   - Misuse of roles causes command rejection (Result::InvalidRole)
 */

#include "utils/test/Tester.h"
#include "Gpu/Ipc/Communications.h"
#include "Gpu/Ipc/Message.h"
#include "Gpu/Ipc/Response.h"
#include "Gpu/Ipc/Result.h"

#include <unistd.h>

using Gpu::Ipc::Communications;
using Gpu::Ipc::Message;
using Gpu::Ipc::Response;
using Gpu::Ipc::Result;

int main() {
    Tester tester("Gpu::Ipc::Communications access control");

    int parentToChild[2];
    int childToParent[2];
    pipe(parentToChild);  // parent to child
    pipe(childToParent);  // child to parent

    const Communications parent(parentToChild, childToParent, true);
    const Communications child(parentToChild, childToParent, false);

    // Role validation
    tester.assertTrue(parent.validateParentAccess(), "Parent validates as parent");
    tester.assertFalse(parent.validateChildAccess(), "Parent does not validate as child");

    tester.assertTrue(child.validateChildAccess(), "Child validates as child");
    tester.assertFalse(child.validateParentAccess(), "Child does not validate as parent");

    // Attempt misuse: child sends Message (invalid)
    constexpr Message bogus;
    const Result r1 = child.send(bogus);
    tester.assertEqual(r1, Result::InvalidRole, "Child cannot send Message");

    // Attempt misuse: parent sends Response (invalid)
    constexpr Response bogusResp;
    const Result r2 = parent.send(bogusResp);
    tester.assertEqual(r2, Result::InvalidRole, "Parent cannot send Response");

    tester.pass();
}
