#file: build_crsce.cmake
include(glob_sources)

# Build the crsce binary
add_executable(crsce ${CRSCE_SOURCES})
