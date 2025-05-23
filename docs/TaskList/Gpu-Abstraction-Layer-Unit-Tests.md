GPU Abstraction Layer Unit Tests
================================

## Part 1: GoogleTest Integration Checklist

| Step	 | Task Description	                                                                       | 
|-------|-----------------------------------------------------------------------------------------|
| 1     | Add GoogleTest via FetchContent, submodule, or package manager in CMakeLists.txt        |
| 2     | Create top-level tests/CMakeLists.txt with add_executable() and target_link_libraries() |
| 3     | Define add_test() targets using enable_testing()                                        |
| 4     | Confirm make test or ctest runs test binaries                                           |
| 5     | Add CI support to run ctest or make test (e.g., GitHub Actions, GitLab CI, etc.)        |
| 6     | Stub a base main.cpp to initialize GTest                                                |
| 7     | Add .gtestconfig or equivalent editor integration if needed (e.g., CLion, VSCode)       |

## Part 2: Unit Test Requirements Checklist

### 🔧 IPC Subsystem

| Step	                    | Task Description	                                                    |
|--------------------------|----------------------------------------------------------------------|
| Gpu::Ipc::Message        | serialize / deserialize round-trip                                   |
| Gpu::Ipc::Response       | serialize / deserialize round-trip                                   |
| Gpu::Ipc::Communications | send/recv for Message/Response, shutdown behavior, access validation |
| Gpu::Ipc::FailureCodes   | enum coverage                                                        |
| Gpu::Ipc::Result         | enum + stream ops                                                    |

### 🧠 Memory and Kernel Management

| Step	                   | Task Description                                   |
|-------------------------|----------------------------------------------------|
| Gpu::Ipc::MemoryTracker | alloc, free, read/write, invalid handle behavior   |
| Gpu::KernelManager      | register, has, get, erase, clear, throw on missing |
| Gpu::ThreadRegistry     | insert, joinAll, clear, empty                      |
| Gpu::ThreadRuntime      | constructor, run() with valid/invalid kernel       |

### 🧮 Matrix and Math

| Step	             | Task Description	                                              |
|-------------------|----------------------------------------------------------------|
| Gpu::Math::Matrix | ✔ ctor, shape accessors, at(), data integrity, bounds checking |

### 🧩 Emulator Infrastructure

| Step	                 | Task Description	                                                  |
|-----------------------|--------------------------------------------------------------------|
| Gpu::Device::Emulator | ✔ constructor, init, shutdown, alloc/free, read/write, kernel/task |
| Gpu::Device::MockGpu  | ✔ boot loop, dispatch logic                                        |
| Gpu::RuntimeManager   | ✔ handle*() method routing, response correctness                   |

### 🔗 Interface Compliance

| Step	                         | Task Description	                                            |
|-------------------------------|--------------------------------------------------------------|
| Gpu::Device::Interface        | ✔ mock + stub type check coverage                            |
| Gpu::Device::{Cuda,Roc,Metal} | ✔ stub enforcement only (should not compile functional code) |

