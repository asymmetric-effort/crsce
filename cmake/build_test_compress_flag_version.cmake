# file: cmake/build_test_compress_flag_version.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build the flag-version test executable
add_executable(test_compress_flag_version ${PROJECT_ROOT}/test/compress-flag-version.cpp)

set_target_properties(test_compress_flag_version
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
