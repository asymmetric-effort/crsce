# file: cmake/build_all.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Build all enabled projects (see feature flags defined in CMakeLists.txt)

include(build_compress)
include(build_decompress)
# ToDo: add more command artifacts here
include(build_test_compress_flag_usage)
include(build_test_compress_flag_version)
include(build_test_decompress_flag_usage)
include(build_test_decompress_flag_version)
include(build_test_file_readInputBuffer_verification)
include(build_test_CrossSumValue)
# ToDo: add more test artifacts here

add_custom_target(build_all
        COMMENT "Build all the projects"
        DEPENDS
        compress
        decompress
        test_compress_flag_usage
        test_compress_flag_version
        test_decompress_flag_usage
        test_decompress_flag_version
        test_file_readInputBuffer_verification
        test_CrossSumValue
        VERBATIM
)
