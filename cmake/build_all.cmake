# build_all.cmake
# Build all enabled projects (see feature flags defined in CMakeLists.txt
include(build_crsce)
# ToDo: add more command artifacts here
include(build_test_flag_version)
include(build_test_flag_usage)
# ToDo: add more test artifacts here

add_custom_target(build_all
    COMMENT("build all the projects")
    DEPENDS test_flag_usage
            test_flag_version
            crsce
    VERBATIM
)