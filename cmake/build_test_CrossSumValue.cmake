# file: cmake/build_test_CrossSumValue.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build the flag-version test executable
add_executable(test_CrossSumValue
        ${CRSCE_SOURCES}
        ${PROJECT_ROOT}/test/CrossSumValue.cpp)

set_target_properties(test_CrossSumValue
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
