# file: cmake/build-test-executables.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

include(load_openssl)

# Build all test/* executables
foreach(test_program ${TEST_PROGRAMS})
    get_filename_component(test_target ${test_program} NAME_WE)
    add_executable(${test_target} ${test_program} ${CRSCE_SOURCES})
    load_openssl(${test_target})
    set_target_properties(${test_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    list(APPEND ALL_TARGETS ${test_target})
endforeach()
