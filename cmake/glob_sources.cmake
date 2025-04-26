# file: cmake/glob_sources.cmake

if(NOT DEFINED CRSCE_SOURCES)
    message(STATUS "Globbing sources...")

    # 1. Glob utility files first
    file(GLOB_RECURSE CRSCE_UTILS_SOURCES "src/utils/**/*.cpp")
    message(STATUS "UTILS_GLOBBED: ${CRSCE_UTILS_SOURCES}")

    # 2. Then glob everything else (excluding utils if necessary)
    file(GLOB_RECURSE CRSCE_OTHER_SOURCES "src/**/*.cpp")

    # 3. Filter to exclude already-globbed utils (optional)
    list(REMOVE_ITEM CRSCE_OTHER_SOURCES ${CRSCE_UTILS_SOURCES})

    # 4. Combine in order
    set(CRSCE_SOURCES ${CRSCE_UTILS_SOURCES} ${CRSCE_OTHER_SOURCES})

    message(STATUS "SOURCES_GLOBBED_FINAL: ${CRSCE_SOURCES}")
endif()
