# file: cmake/apple-llvm-homebrew.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

set(CMAKE_OSX_SYSROOT "" CACHE PATH "Clear macOS sysroot to prevent libc++ conflicts" FORCE)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "" FORCE)

set(CMAKE_SYSTEM_NAME Darwin)
set(LLVM_ROOT "/usr/local/opt/llvm")
set(CMAKE_PREFIX_PATH "/usr/local/opt/llvm")

set(CMAKE_C_COMPILER   "${CMAKE_PREFIX_PATH}/bin/clang"   CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "${CMAKE_PREFIX_PATH}/bin/clang++" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -lc++ -lc++abi")

include_directories(BEFORE "/usr/local/opt/llvm/include/c++/v1")

link_directories("/usr/local/opt/llvm/lib")
