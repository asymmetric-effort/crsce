// file: src/Gpu/Device/PointerTracker.h
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#pragma once

#include <unordered_set>

namespace Gpu {
    using PointerTracker = std::unordered_set<void*>;
}
