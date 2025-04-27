#file: build_compress.cmake
include(glob_sources)

# Build the crsce compression binary
add_executable(compress cmd/compress.cpp ${CRSCE_SOURCES})

target_include_directories(compress PRIVATE ${PROJECT_ROOT}/include)

set_target_properties(compress
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
