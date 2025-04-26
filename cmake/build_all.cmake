# build_all.cmake
# Build all enabled projects (see feature flags defined in CMakeLists.txt
include(build_compress)
include(build_decompress)

add_custom_target(build_all
    COMMENT("build all the projects")
    ${CMAKE_COMMAND} --build build --target compress
    ${CMAKE_COMMAND} --build build --target decompress
    DEPENDS compress
            decompress
    VERBATIM
)