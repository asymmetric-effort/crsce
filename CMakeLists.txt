# file: CMakeLists.txt
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

cmake_minimum_required(VERSION 3.27.4)

project(crsce VERSION 1.0.0)
set(COPYRIGHT "(c) 2025 Asymmetric Effort, LLC.  All Rights Reserved.")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS -stdlib=libc++)
set(CMAKE_CXX_LINKER_FLAGS -lc++ -lc++abi)
set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++" CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "" FORCE)

if(APPLE)
    message(STATUS "Disabling default macOS SDK sysroot to allow Homebrew libc++ usage")
    set(CMAKE_OSX_SYSROOT "" CACHE PATH "Clear macOS sysroot to prevent libc++ conflicts" FORCE)
endif()

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

add_compile_definitions(
        COPYRIGHT="${COPYRIGHT}"
        PROJECT_NAME="${PROJECT_NAME}"
        PROJECT_VERSION="${PROJECT_VERSION}"
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_ROOT}/cmake")

include(include_directories)
include(build_all)
