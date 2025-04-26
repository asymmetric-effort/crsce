# file: cmake/build_test_flag_version.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build the flag-version test executable
add_executable(test_flag_version ${PROJECT_ROOT}/test/flag-version.cpp)
