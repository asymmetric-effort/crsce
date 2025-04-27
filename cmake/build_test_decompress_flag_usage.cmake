# file: cmake/build_test_decompress_flag_usage.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

add_executable(test_decompress_flag_usage ${PROJECT_ROOT}/test/decompress-flag-usage.cpp)

set_target_properties(test_decompress_flag_usage
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
