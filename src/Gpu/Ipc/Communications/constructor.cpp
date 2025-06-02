/**
 * @file src/Gpu/Ipc/Communications/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Communications.h"

/**
 * @namespace Gpu::Device
 * @brief Namespace for GPU device abstractions and implementations.
 */
namespace Gpu::Ipc {
    /**
     * @name constructor
     * @class Communications
     * @public
     * @brief class constructor enumerates two p2c and two c2p file descriptors.
     * @ref docs/Gpu/Design/Gpu-Ipc-Communications.md
     * @param parentToChild int file handle array
     * @param childToParent int file handle array
     * @param isParentProcess bool
     */
    Communications::Communications(const int parentToChild[ipcPipeFdSz], const int childToParent[ipcPipeFdSz], const bool isParentProcess)
        : isParent(isParentProcess) {
        parentToChildFd[readEndpoint] = parentToChild[readEndpoint];
        parentToChildFd[writeEndpoint] = parentToChild[writeEndpoint];
        childToParentFd[readEndpoint] = childToParent[readEndpoint];
        childToParentFd[writeEndpoint] = childToParent[writeEndpoint];
    }

}
