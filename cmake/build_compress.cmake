#file: build_compress.cmake
include(glob_sources)

# Build the crsce binary
add_executable(compress ${CRSCE_SOURCES})
