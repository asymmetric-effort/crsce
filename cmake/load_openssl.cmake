# file: cmake/load_openssl.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Usage:
#   load_openssl(TARGET_NAME)
#
# Example:
#   load_openssl(my_program)

function(load_openssl target_name)
    find_package(OpenSSL QUIET)

    if (OpenSSL_FOUND)
        target_link_libraries(${target_name} PRIVATE OpenSSL::Crypto)
        message(STATUS "Linked ${target_name} with OpenSSL::Crypto")
    else()
        message(WARNING "OpenSSL not found. ${target_name} will not have OpenSSL linkage.")
    endif()
endfunction()
