/**
 * @file include/Common/KernelTable.h
 * @brief a list of KernelDescriptors for GPU Kernels
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

#include "Common/KernelDescriptor.h"

namespace Common {
    /**
     * @name KernelTable
     * @brief A List of KernelDescriptor objects
     */
    using KernelTable = std::vector<KernelDescriptor>;

    /**
     * @name serialize (KernelTable)
     * @brief Serialize a list of KernelDescriptor objects
     * @param buf Buffer8
     * @param table KernelTable
     */
    inline void serialize(Buffer8& buf, const KernelTable& table) {
        const size_t table_size = table.size();
        Common::serialize(buf, table_size); // we need the table size to be first.
        for (auto const& thisKernelDescriptor : table) {
            auto serializedKernelDescriptor = thisKernelDescriptor.serialize();
            buf.insert(
                buf.end(),
                serializedKernelDescriptor.begin(),
                serializedKernelDescriptor.end()
            );
        }
    }

    /**
     * @name deserialize (kernelTable)
     * @brief Deserialize a list of KernelDescriptor objects
     * @param buf Buffer8
     * @return table KernelTable
     */
    inline KernelTable deserialize(const Buffer8& buf) {
        KernelTable table;
        const auto table_size = Common::deserialize<size_t>(buf, 1);
        for (auto i = 0; i < table_size; ++i) {
            KernelDescriptor thisKernel;
            thisKernel.deserialize(buf);
            table.emplace_back(thisKernel);
        }
        return table;
    }
}
