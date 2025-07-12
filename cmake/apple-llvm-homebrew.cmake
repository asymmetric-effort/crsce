# file: cmake/apple-llvm-homebrew.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

set(CMAKE_OSX_SYSROOT "" CACHE PATH "Clear macOS sysroot to prevent libc++ conflicts" FORCE)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "" FORCE)

set(CMAKE_SYSTEM_NAME Darwin)

# Dynamically find LLVM path via Homebrew
execute_process(
        COMMAND brew --prefix llvm
        OUTPUT_VARIABLE LLVM_ROOT
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_PREFIX_PATH "${LLVM_ROOT}")

set(CMAKE_C_COMPILER   "${CMAKE_PREFIX_PATH}/bin/clang"   CACHE STRING "" FORCE)

set(CMAKE_CXX_COMPILER "${CMAKE_PREFIX_PATH}/bin/clang++" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -lc++ -lc++abi")

include_directories(BEFORE "${LLVM_ROOT}/include/c++/v1")

link_directories("${LLVM_ROOT}/lib")