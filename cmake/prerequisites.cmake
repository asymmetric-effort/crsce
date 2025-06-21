# file: cmake/prerequisites.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

if(APPLE)
    include("cmake/apple-llvm-homebrew.cmake")
else ()

endif()

# Note: we can add more prereqs here.
