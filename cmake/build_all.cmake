# file: cmake/build_all.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

include(glob_sources)
include(glob_programs)
include(glob_tests)

set(ALL_TARGETS)

include(build-command-executables)
include(build-test-executables)

# Create unified build_all target
add_custom_target(build_all
        DEPENDS ${ALL_TARGETS}
)
