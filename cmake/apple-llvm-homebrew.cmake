# file: cmake/apple-llvm-homebrew.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

message(STATUS "Disabling default macOS SDK sysroot to allow Homebrew libc++ usage")
set(CMAKE_OSX_SYSROOT "" CACHE PATH "Clear macOS sysroot to prevent libc++ conflicts" FORCE)

set(CMAKE_SYSTEM_NAME Darwin)
set(LLVM_ROOT "/usr/local/opt/llvm")
set(CMAKE_PREFIX_PATH "/usr/local/opt/llvm")

set(CMAKE_C_COMPILER   "${CMAKE_PREFIX_PATH}/bin/clang"   CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "${CMAKE_PREFIX_PATH}/bin/clang++" CACHE STRING "" FORCE)

include_directories(BEFORE "/usr/local/opt/llvm/include/c++/v1")

link_directories("/usr/local/opt/llvm/lib")
