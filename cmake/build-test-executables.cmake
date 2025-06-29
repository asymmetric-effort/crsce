# cmake/build-test-executables.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

include(load_openssl)

# Build all test/* executables, numbered by position in TEST_PROGRAMS
set(_test_idx 0)
foreach(test_program IN LISTS TEST_PROGRAMS)
    # Extract the base name (without extension) of the .cpp
    get_filename_component(_base_name ${test_program} NAME_WE)

    # Form the indexed target name: 0_name, 1_name, …
    set(_test_target "${_test_idx}_${_base_name}")

    # Create the executable
    add_executable(${_test_target} ${test_program} ${CRSCE_SOURCES})
    load_openssl(${_test_target})
    set_target_properties(
            ${_test_target}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
    )

    # Collect for possible batch operations
    list(APPEND ALL_TARGETS ${_test_target})

    # Increment the index
    math(EXPR _test_idx "${_test_idx} + 1")
endforeach()
