/**
 * @file include/Gpu/Ipc/Message/GpuInitialize.h
 * @brief Define an IPC Message class representing the GPU-initialize message
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once

namespace Gpu::Ipc::Message {
    /**
     * @enum GpuType
     * @brief Enumerate the supported GPU types
     */
    enum class GpuType : uint8_t {
        Emulator = 0x00,
        Cuda = 0x01,
        AmdRoc = 0x02,
        AppleMetal = 0x03,
        MaxGpuType = AppleMetal,
    };

    /**
     * @name GpuTypeToString
     * @brief Return the text version of a GpuType value.
     * @param type
     * @return
     */
    inline std::string GpuTypeToString(const GpuType &type) {
        switch (type) {
        case GpuType::Emulator:
            return "Emulator";
        case GpuType::Cuda:
            return "Cuda";
        case GpuType::AmdRoc:
            return "AmdRoc";
        case GpuType::AppleMetal:
            return "AppleMetal";
        default:
            throw std::runtime_error("Unknown Gpu Type");
        }
    }
}
