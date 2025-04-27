# file: cmake/build_test_decompress_flag_version.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build the flag-version test executable
add_executable(test_decompress_flag_version ${PROJECT_ROOT}/test/decompress-flag-version.cpp)

set_target_properties(test_decompress_flag_version
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
