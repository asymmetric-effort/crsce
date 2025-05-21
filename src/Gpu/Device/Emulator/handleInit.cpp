// file: src/Gpu/Device/handleInit.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"
#include <iostream>

namespace Gpu {

    void Emulator::handleInit(const int toParentFd) {
        perror("[Emulator] handleInit() sending Init ACK\n");

        IpcResponseMsg response;
        response.status = 0;  // Indicate success
        response.size   = 0;  // No payload expected

        if (const ssize_t written = write(toParentFd, &response, sizeof(response)); written != sizeof(response)) {
            std::cerr << "[Emulator::handleInit] Failed to write full Init response: wrote "
                      << written << " of " << sizeof(response) << " bytes\n";
        }
    }
} // namespace Gpu
