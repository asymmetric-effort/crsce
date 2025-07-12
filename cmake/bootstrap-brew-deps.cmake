# file: cmake/bootstrap-brew-deps.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# List of required tools to check and install
set(REQUIRED_TOOLS ninja ccache llvm gcc)

foreach(tool IN LISTS REQUIRED_TOOLS)
    # Check if the tool exists
    execute_process(
            COMMAND which ${tool}
            RESULT_VARIABLE _found_${tool}
            OUTPUT_QUIET ERROR_QUIET
    )

    if(NOT _found_${tool} EQUAL 0)
        message(STATUS "Installing ${tool} via Homebrew...")
        execute_process(
                COMMAND brew install ${tool}
                RESULT_VARIABLE _install_result
        )
        if(NOT _install_result EQUAL 0)
            message(FATAL_ERROR "Failed to install ${tool} via Homebrew")
        endif()
    else()
        message(STATUS "${tool} already installed.")
    endif()
endforeach()
