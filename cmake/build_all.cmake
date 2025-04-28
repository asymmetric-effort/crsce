# file: cmake/build_all.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

include(glob_sources)
include(glob_programs)
include(glob_tests)

set(ALL_TARGETS)

# Build all cmd/ executables
foreach(cmd_program ${CMD_PROGRAMS})
    get_filename_component(cmd_target ${cmd_program} NAME_WE)
    add_executable(${cmd_target} ${cmd_program} ${CRSCE_SOURCES})
    set_target_properties(${cmd_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    list(APPEND ALL_TARGETS ${cmd_target})
endforeach()

# Build all test/ executables
foreach(test_program ${TEST_PROGRAMS})
    get_filename_component(test_target ${test_program} NAME_WE)
    add_executable(${test_target} ${test_program} ${CRSCE_SOURCES})
    set_target_properties(${test_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
    list(APPEND ALL_TARGETS ${test_target})
endforeach()

# Create unified build_all target
add_custom_target(build_all
        DEPENDS ${ALL_TARGETS}
)
