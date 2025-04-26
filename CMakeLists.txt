#file: CMakeLists.txt
cmake_minimum_required(VERSION 3.27.4)

project(crsce)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

# Custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_ROOT}/cmake")

include(include_directories)
include(build_all)

