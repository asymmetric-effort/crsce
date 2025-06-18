# file: cmake/lint_makefile.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>


# Makefile syntax check
add_custom_target(lint_makefile
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_SOURCE_DIR} --target help || exit 1
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Checking Makefile syntax"
)
