# file: cmake/lint_cpp.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

find_program(CPPCHECK cppcheck)

# C++ lint (cppcheck)
if(CPPCHECK)
    file(GLOB_RECURSE CPP_SOURCES
            "${CMAKE_SOURCE_DIR}/src/*.cpp"
            "${CMAKE_SOURCE_DIR}/include/*.h"
            "${CMAKE_SOURCE_DIR}/test/*.cpp")
    add_custom_target(lint_cpp
            COMMAND ${CPPCHECK}
            --enable=all
            --inconclusive
            --quiet
            --suppress=unusedFunction
            --std=c++20
            -i ${PROJECT_SOURCE_DIR}/test
            -I ${CMAKE_SOURCE_DIR}/include
            -I ${CMAKE_SOURCE_DIR}/src
            ${CPP_SOURCES} || exit 1
            COMMENT "Running cppcheck (suppressing unusedFunction)"
    )
else()
    message(WARNING "cppcheck not found; skipping lint_cpp target")
endif()

