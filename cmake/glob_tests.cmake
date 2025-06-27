# Glob all test programs
file(GLOB_RECURSE TEST_PROGRAMS
        CONFIGURE_DEPENDS
        "${PROJECT_ROOT}/test/*.cpp")
