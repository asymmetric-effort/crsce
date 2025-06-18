# file: cmake/lint_cpp.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

find_program(CPPCHECK cppcheck)

# C++ lint (cppcheck)
if (CPPCHECK)
    # Collect all C++ sources (including tests, which are separately suppressed via .cppcheck-suppressions.txt)
    file(GLOB_RECURSE CPP_SOURCES
            "${CMAKE_SOURCE_DIR}/src/*.cpp"
            "${CMAKE_SOURCE_DIR}/include/*.h"
            "${CMAKE_SOURCE_DIR}/test/*.cpp"
    )

    # Phony target that runs cppcheck over each source file
    add_custom_target(lint_cpp
            COMMENT "Running cppcheck over all sources"
    )

    foreach (SOURCE_FILE IN LISTS CPP_SOURCES)
        add_custom_command(
                TARGET lint_cpp
                POST_BUILD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${CPPCHECK}
                --enable=all
                --quiet
                --platform=unix64
                --std=c++${CMAKE_CXX_STANDARD}
                --language=c++
                --check-level=normal
                --inline-suppr
                --error-exitcode=10
                --suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions.txt
                "${SOURCE_FILE}"
                COMMENT "Linting ${SOURCE_FILE}"
        )
    endforeach ()
else ()
    message(WARNING "cppcheck not found; skipping lint_cpp target")
endif ()
