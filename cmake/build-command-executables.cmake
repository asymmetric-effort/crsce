# file: cmake/build-command-executables.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build all cmd/* executables
foreach(cmd_program ${CMD_PROGRAMS})
    get_filename_component(cmd_target ${cmd_program} NAME_WE)
    add_executable(${cmd_target} ${cmd_program} ${CRSCE_SOURCES})
    set_target_properties(${cmd_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    list(APPEND ALL_TARGETS ${cmd_target})
endforeach()
