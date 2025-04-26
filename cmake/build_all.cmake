# build_all.cmake
# Build all enabled projects (see feature flags defined in CMakeLists.txt

include(build_compress)
include(build_decompress)
# ToDo: add more command artifacts here
include(build_test_compress_flag_usage)
include(build_test_compress_flag_version)
# ToDo: add more test artifacts here

add_custom_target(build_all
        COMMENT "Build all the projects"
        ${CMAKE_COMMAND} --build build --target compress
        ${CMAKE_COMMAND} --build build --target decompress
        ${CMAKE_COMMAND} --build build --target test_compress_flag_usage
        ${CMAKE_COMMAND} --build build --target test_compress_flag_version
        DEPENDS compress decompress test_compress_flag_usage test_compress_flag_version
        VERBATIM
)
