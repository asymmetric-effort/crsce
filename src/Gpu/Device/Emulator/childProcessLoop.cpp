// file: src/Gpu/Device/childProcessLoop.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "Gpu/Device/Emulator/Emulator.h"

namespace Gpu {

    namespace {
        void handleAlloc(const IpcHeader& hdr, int fromChildFd, std::unordered_set<void*>& allocations) {
            void* ptr = std::malloc(hdr.size);
            if (ptr) allocations.insert(ptr);
            write(fromChildFd, &ptr, sizeof(ptr));
        }

        void handleFree(const IpcHeader& hdr, std::unordered_set<void*>& allocations) {
            void* ptr = reinterpret_cast<void*>(hdr.ptr);
            auto it = allocations.find(ptr);
            if (it != allocations.end()) {
                std::free(ptr);
                allocations.erase(it);
            }
        }

        void handleWrite(int toChildFd_, const IpcHeader& hdr) {
            void* dst = reinterpret_cast<void*>(hdr.ptr);
            std::vector<char> buf(hdr.size);
            read(toChildFd_, buf.data(), hdr.size);
            std::memcpy(dst, buf.data(), hdr.size);
        }

        void handleRead(int fromChildFd_, const IpcHeader& hdr, const std::unordered_set<void*>& allocations) {
            void* src = reinterpret_cast<void*>(hdr.ptr);
            if (allocations.find(src) == allocations.end()) {
                std::cerr << "[Emulator] ReadBuffer failed: invalid or freed pointer.\n";
                char fail = 1;
                write(fromChildFd_, &fail, 1);
                return;
            }
            std::vector<char> buf(hdr.size);
            std::memcpy(buf.data(), src, hdr.size);
            write(fromChildFd_, buf.data(), hdr.size);
        }

        void handleLaunchTask(const IpcHeader& hdr) {
            auto kernel = KernelRegistry::instance().get(static_cast<KernelId>(hdr.kernelId));
            if (kernel && hdr.size > 0) {
                void* buffer = reinterpret_cast<void*>(hdr.ptr);
                kernel->run(buffer, hdr.size);
            }
        }

        void handleWait(int fromChildFd_) {
            char ack = 0;
            write(fromChildFd_, &ack, 1);
        }

        void handleReset(std::unordered_set<void*>& allocations) {
            for (void* ptr : allocations) {
                std::free(ptr);
            }
            allocations.clear();
            std::cerr << "[Emulator] All GPU buffers freed. Emulator reset.\n";
        }
    }

    void Emulator::childProcessLoop() {

        while (true) {
            IpcHeader hdr;
            ssize_t n = read(toChildFd_, &hdr, sizeof(hdr));
            if (n != sizeof(hdr)) break;

            switch (hdr.type) {
                case CommandType::Alloc:
                    handleAlloc(hdr, fromChildFd_, allocations_);
                    break;
                case CommandType::Free:
                    handleFree(hdr, allocations_);
                    break;
                case CommandType::Write:
                    handleWrite(toChildFd_, hdr);
                    break;
                case CommandType::Read:
                    handleRead(fromChildFd_, hdr, allocations_);
                    break;
                case CommandType::LaunchTask:
                    handleLaunchTask(hdr);
                    break;
                case CommandType::Wait:
                    handleWait(fromChildFd_);
                    break;
                case CommandType::Reset:
                    handleReset(allocations_);
                    break;
                case CommandType::Shutdown:
                    handleReset(allocations_);
                    std::cerr << "[Emulator] Shutdown received. Exiting.\n";
                    return;
                default:
                    std::cerr << "[Emulator] Unknown command " << static_cast<int>(hdr.type) << std::endl;
                    break;
            }
        }
    }

} // namespace Gpu
