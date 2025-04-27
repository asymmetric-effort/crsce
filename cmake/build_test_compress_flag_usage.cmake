# file: cmake/build_test_compress_flag_usage.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

add_executable(test_compress_flag_usage test/compress-flag-usage.cpp)

set_target_properties(test_compress_flag_usage
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
