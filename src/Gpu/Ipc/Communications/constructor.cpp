/**
 * @file src/Gpu/Ipc/Channel/constructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "Gpu/Ipc/Channel.h"

namespace Gpu::Ipc {
    Channel::Channel(){
        pipe(requestPipe.data());
        pipe(responsePipe.data());
    }
}
