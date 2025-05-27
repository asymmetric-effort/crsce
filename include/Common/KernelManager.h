/**
 * @file include/Common/KernelManager.h
 * @brief Declare and manage a GPU kernel blob manager which allows the consumer to register and manage GPU kernel
 *        binary code (blobs) for execution.
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once
#include <unordered_map>
#include <mutex>
#include "Common/Buffer8.h"
#include "Common/KernelId.h"
/**
 * @namespace Common
 * @brief A common CRSCE namespace for reusable generic functionality.
 */
namespace Common {
    /**
     * @name Common::KernelManager
     * @brief Tracks and manages GPU kernel blobs by ID.
     * @ref docs/Gpu/Design/Gpu-KernelManager.md
     *
     * Stores binary blobs indexed by kernel ID. Blobs are immutable and thread-safe.
     */
    class KernelManager final {
    public:
        /**
         * @name constructor
         * @brief default constructor
         */
        KernelManager()=default;

        /**
         * @name destructor
         * @brief default destructor
         */
        ~KernelManager()=default;

        /**
         * @name clear
         * @class KernelManager
         * @brief Lock and clear the contents of the KernelManager.
         * @return bool (success=true, failure=false)
         */
        bool clear();
        /**
         * @name erase
         * @class KernelManager
         * @brief Erase a given record from the KernelManager
         * @param id Common::KernelId
         * @return bool (success=true, failure=false)
         */
        bool erase(const Common::KernelId id);
        /**
         * @name get
         * @class KernelManager
         * @brief Retrieve a Kernel binary blob given its KernelId
         * @param id Common::KernelId
         * @return Common::Buffer8
         */
        const Common::Buffer8& get(Common::KernelId id) const;
        /**
         * @name has
         * @class KernelManager
         * @brief Return true if KernelManager has a record with the given KernelId value.
         * @param id Common::KernelId
         * @return bool
         */
        bool has(Common::KernelId id) const;
        /**
         * @name registerKernel
         * @brief Given a kernel binary (blob) using Common::Buffer8 and a KernelId), create an entry to store and
         *        track the binary.
         * @param id Common::KernelId
         * @param binary Common::Buffer8
         * @return bool (success=true, failure=false)
         */
        bool registerKernel(Common::KernelId id, const Common::Buffer8& binary);

    private:
        /**
         * @name mutex_
         * @brief A mutex lock for thread safety.
         */
        mutable std::mutex mutex_;
        /**
         * @name table_
         * @brief A map to store the KernelId and a kernel binary blob.
         */
        std::unordered_map<Common::KernelId, Common::Buffer8> table_;
    };

} // namespace Gpu
