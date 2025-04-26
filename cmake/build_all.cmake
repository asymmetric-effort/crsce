# build_all.cmake
# Build all enabled projects (see feature flags defined in CMakeLists.txt
include(build_crsce)
# ToDo: add more here

add_custom_target(build_all
    COMMENT("build all the projects")
    DEPENDS crsce
    VERBATIM
)