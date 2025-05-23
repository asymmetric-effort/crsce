// file: src/Gpu/ThreadRegistry/joinAll.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include <ranges>

#include "Gpu/ThreadRegistry.h"

namespace Gpu {

    void ThreadRegistry::joinAll() {
        std::lock_guard lock(mutex_);
        for (auto &thread: table_ | std::views::values) {
            if (thread.joinable()) thread.join();
        }
        table_.clear();
    }

}
