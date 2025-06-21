# file: cmake/concurrency.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

function(configure_concurrency)
    include(CheckIncludeFileCXX)
    include(CheckCXXCompilerFlag)

    # Detect core count (portable)
    if(UNIX AND NOT APPLE)
        execute_process(
                COMMAND nproc
                OUTPUT_VARIABLE CPU_COUNT
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    elseif(APPLE)
        execute_process(
                COMMAND sysctl -n hw.ncpu
                OUTPUT_VARIABLE CPU_COUNT
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    elseif(WIN32)
        execute_process(
                COMMAND powershell -Command "$env:NUMBER_OF_PROCESSORS"
                OUTPUT_VARIABLE CPU_COUNT
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    else()
        set(CPU_COUNT 1)
    endif()

    if(NOT CPU_COUNT OR CPU_COUNT EQUAL 0)
        set(CPU_COUNT 1)
    endif()

    message(STATUS "Detected CPU core count: ${CPU_COUNT}")
    set(CONCURRENCY_J_ARG "-j${CPU_COUNT}" CACHE STRING "Parallel build job flag")

    # Store result for external script use
    file(WRITE "${CMAKE_BINARY_DIR}/concurrency.build.flag" "${CONCURRENCY_J_ARG}\n")
endfunction()
