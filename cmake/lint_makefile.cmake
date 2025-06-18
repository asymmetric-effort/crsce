# file: cmake/lint_makefile.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

find_program(MAKE_TOOL make)

# Makefile syntax check
add_custom_target(lint_makefile
        COMMAND ${MAKE_TOOL} -n -s || exit 1
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Checking Makefile syntax"
)
