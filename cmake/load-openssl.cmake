# cmake/load-openssl.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Assume openssl@3 was installed via bootstrap-brew-deps.cmake
execute_process(
    COMMAND brew --prefix openssl@3
    OUTPUT_VARIABLE OPENSSL_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(OPENSSL_ROOT_DIR "${OPENSSL_PREFIX}" CACHE PATH "OpenSSL root directory")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_PREFIX}/include" CACHE PATH "OpenSSL include directory")
set(OPENSSL_LIBRARIES "${OPENSSL_PREFIX}/lib" CACHE PATH "OpenSSL library directory")
