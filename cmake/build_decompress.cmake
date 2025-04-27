#file: build_decompress.cmake
include(glob_sources)

# Build the crsce decompression binary
add_executable(decompress cmd/decompress.cpp ${CRSCE_SOURCES})

add_compile_definitions(PROJECT_NAME="decompress")

target_include_directories(decompress PRIVATE ${PROJECT_ROOT}/include)

set_target_properties(decompress
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
