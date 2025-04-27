# file: cmake/glob_sources.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

if (NOT DEFINED CRSCE_SOURCES)
    message(STATUS "Globbing sources...")

    file(GLOB_RECURSE CRSCE_SOURCES "src/**/*.cpp")

    message(STATUS "SOURCES_GLOBBED: ${CRSCE_SOURCES}")

endif ()
