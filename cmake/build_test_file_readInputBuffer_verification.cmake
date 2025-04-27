# file: cmake/build_test_file_readInputBuffer_verification.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build the test_file_readInputBuffer_verification test executable
add_executable(test_file_readInputBuffer_verification ${PROJECT_ROOT}/test/file-readInputBuffer-verification.cpp)

target_include_directories(test_file_readInputBuffer_verification PRIVATE ${PROJECT_ROOT}/include)

set_target_properties(test_file_readInputBuffer_verification
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
