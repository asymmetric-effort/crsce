# file: cmake/prerequisites.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

include("${CMAKE_SOURCE_DIR}/cmake/concurrency.cmake")

configure_concurrency()

if(APPLE)
    include("cmake/bootstrap-brew-deps.cmake")
    include("cmake/apple-llvm-homebrew.cmake")
else ()

endif()

# Note: we can add more prereqs here.
