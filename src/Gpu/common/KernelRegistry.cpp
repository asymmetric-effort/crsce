// file: src/Gpu/KernelRegistry.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/common/KernelRegistry.h"

namespace Gpu {

    KernelRegistry& KernelRegistry::instance() {
        static KernelRegistry inst;
        return inst;
    }

    void KernelRegistry::registerKernel(KernelId id, Kernel* kernel) {
        table_[id] = std::unique_ptr<Kernel>(kernel);
    }

    Kernel* KernelRegistry::get(KernelId id) const {
        auto it = table_.find(id);
        if (it != table_.end()) return it->second.get();
        return nullptr;
    }

} // namespace Gpu
