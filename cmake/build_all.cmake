# build_all.cmake
# Build all enabled projects (see feature flags defined in CMakeLists.txt
include(build_compress)
# ToDo: add more command artifacts here
include(build_test_compress_flag_usage)
include(build_test_compress_flag_version)
# ToDo: add more test artifacts here

add_custom_target(build_all
    COMMENT("build all the projects")
    DEPENDS test_compress_flag_usage
            test_compress_flag_version
            compress
    VERBATIM
)